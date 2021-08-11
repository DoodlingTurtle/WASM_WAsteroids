#include "ship.h"
#include <math.h>
#include <stdio.h>

#include "../config.h"
#include "../global.h"
#include "../collision.h"

#include "ship/shipupgrade_shield.h"
#include "ship/shipupgrade_cannon.h"

#define SHIP_DEFAULT_RADIUS 16.0f

Ship::Ship() 
: SpaceObj(SHIP_DEFAULT_RADIUS)
  , angRes(PI)
  , thrusting(false)
  , sprShip(nullptr)
  , decShip(nullptr)
  , sfxThrust(nullptr)
  , sfxExplode(nullptr)
  , chaThrust(-1)
  , selectedComponent(0)
{
    sprShip = new olc::Sprite("./assets/sprites/ship.png");
    decShip = new olc::Decal(sprShip);    

    sprDissolve = new olc::Sprite(32, 32);
    Global::pge->SetDrawTarget(sprDissolve);
    Global::pge->DrawPartialSprite({ 0, 0 }, sprShip, { 32, 0 }, { 32, 32 });
    Global::pge->SetDrawTarget(nullptr);

    sfxThrust  = Mix_LoadWAV("assets/sfx/cc0_nocredit/loop_ambient_01.ogg");
    sfxExplode = Mix_LoadWAV("assets/sfx/sci-fi_sounds/explosionCrunch_004.ogg");

    this->bIsAlive = true;
    stats = Global::shipStats;

    reset();

    stats->giveComponentsTo(&components);

    for(int a = components.size()-1; a>=0; a--){
        ShipComponent* comp = components.at(a);
        if(!comp || !comp->initShipComponent(stats, this))
            components.erase(components.begin() + a); 
    }

    this->addUpgrade(new ShipUpgrade_Shield());
    this->addUpgrade(new ShipUpgrade_Cannon());

}

Ship::~Ship() {
    stats->takeComponentsFrom(&components);

    Debug("clear upgrades");
    clearUpgrades();

    Debug("clear sfx");
    if(chaThrust != -1) {
        Mix_HaltChannel(chaThrust);
        chaThrust = -1;
    }
    if(sfxThrust != nullptr)
        Mix_FreeChunk(sfxThrust);

    Debug("Delete ship dissolveSpr");
    delete sprDissolve;
    Debug("Delete ship spr");
    delete sprShip;
    Debug("Delete ship dec");
    delete decShip;

}

void Ship::clearUpgrades() {
    currentShield = nullptr;

    for(ShipUpgrade* su : upgrades)
        delete su;

    for(ShipUpgrade* su : newUpgrades)
        delete su;

    upgrades.clear();
    newUpgrades.clear();
}

void Ship::addUpgrade(ShipUpgrade *upgrade) {

    if(upgrade->init(stats))
        newUpgrades.push_back(upgrade);

    // If upgrade is instanceOf ShipUpgrade_Shield, the register as currentShield
    ShipUpgrade_Shield* shieldPtr = dynamic_cast<ShipUpgrade_Shield*>(upgrade);
    if(shieldPtr != nullptr)
        currentShield = shieldPtr;

    Debug("add ship upgrade " << upgrade);
}


void Ship::reset() {
    Debug("ship reset");
    pos.x = APP_SCREEN_WIDTH/2;
    pos.y = APP_SCREEN_HEIGHT/4;
    
    scale = 1;
    setAngleRel(PI/2);
    SpaceObj::setDirection(olc::vf2d((float)cos(PI/2), (float)sin(PI/2)));
    moveVelocity = 0.0f;
    setDirection({0.0f, 0.0f});
    bIsAlive = true;

    clearUpgrades();
    
    objRadius = 24;
    stats->generator = stats->generatorcapacity;

}

RGNDS::Collision::Circle Ship::getCollider() {
    float radius = 14.0f;

    if(currentShield != nullptr)
        radius = currentShield->getRadius();

    return {pos.x, pos.y, radius * scale};
}

void Ship::kill() {
    if(chaThrust != -1) {
        Mix_HaltChannel(chaThrust);
        chaThrust = -1;
    }
    Mix_PlayChannel(-1, sfxExplode, 0);
    SpaceObj::kill();
}

std::vector<SpaceObj*>* Ship::onUpdate(float deltaTime) {

//check asteroids collision
    std::vector<Asteroids::Asteroid*> asteroids = Global::asteroids->getLiveAsteroids();
    RGNDS::Collision c;
    for(auto asteroid : asteroids) {
        if(RGNDS::Collision::checkCircleOnCircle(
            getCollider(), 
            asteroid->getColliders(),
            &c
        )){
            if(currentShield != nullptr) {
                currentShield->gotHit(asteroid, this, &c);
                moveVelocity *= 0.5f;
            }
            else {
                this->kill();
                return nullptr;
            }
        }
    }

    auto ret = new std::vector<SpaceObj*>();

    // Input Rotation
    if(Global::gameInput->held&KEYPAD_RIGHT) setAngleRel(angRes*deltaTime); 
    if(Global::gameInput->held&KEYPAD_LEFT) setAngleRel(-angRes*deltaTime); 

    // Input Component selection
    if(Global::gameInput->pressed&KEYPAD_X) selectedComponent--;
    if(Global::gameInput->pressed&KEYPAD_Y) selectedComponent++;

    int sz = selectableComponents.size()-1;
    if(selectedComponent < 0)   selectedComponent = 0;
    if(selectedComponent > sz)  selectedComponent = sz; 

    // Activate component with A-Key (P on the Keybaord)
    if(sz > -1 && Global::gameInput->pressed&KEYPAD_A) {
        int index = selectableComponents.at(selectedComponent);
        ShipComponent* c = components.at(index);
        if(c) {
            if(!c->invokeShipComponent(stats, this, ret)) {
                delete c;
                c = nullptr;
            }
        }
        if(!c) components.erase(components.begin()+index);
    }


    // Input Thrusting
    thrusting = false;
    bool allowgeneratoregen = true;
    if(Global::gameInput->held&KEYPAD_UP) {
        float consumption = stats->thrustenergyconsumption * deltaTime;
        if(!stats->generatorhalt && stats->generator >= consumption) {
            thrusting = true;
            stats->generator -= consumption;
        }
        else allowgeneratoregen = false;
    }
    
    if(thrusting) {
        shipEngine.accelerate(deltaTime * 15.0f);
        if(chaThrust == -1 || !Mix_Playing(chaThrust)) {
            chaThrust = Mix_PlayChannel(-1, sfxThrust, -1);
        }
    } 
    else {
        shipEngine.decerlerate(1);
        if(chaThrust > -1) {
            Mix_HaltChannel(chaThrust);
            chaThrust = -1;
        }
    }

    if(stats->generator <= stats->generatorlock)
        stats->generatorhalt = true;

    if(stats->generator >= stats->generatorunlock)
        stats->generatorhalt = false;

// Genrator Recovery
    if(allowgeneratoregen) {
        stats->generator += deltaTime * stats->generatorrecovery;
        if(stats->generator > stats->generatorcapacity)
            stats->generator = stats->generatorcapacity;
    }

// Update Components
    for(int a = components.size()-1; a>=0; a--){ 
        ShipComponent* comp = components.at(a);
        if(comp) {
            if(!comp->updateShipComponent(deltaTime)) {
                delete comp;
                comp = nullptr;
            }
        }

        if(!comp)
            components.erase(components.begin() + a); 
    }

// Add new Upgrades
    upgrades.insert(upgrades.end(), newUpgrades.begin(), newUpgrades.end());
    newUpgrades.clear();

// Update upgrades
    ShipUpgrade* upgrade;
    for(int a = upgrades.size()-1; a >= 0; a--) {
        upgrade = upgrades.at(a);
        if(!upgrade->update(stats, this, deltaTime, ret)) {
            if(upgrade == currentShield) {
                currentShield = nullptr;
            //    objRadius = SHIP_DEFAULT_RADIUS;
            }
            Debug("remove ship upgrade " << upgrade);
            delete upgrade;

            upgrades.erase(upgrades.begin()+a);
        }
    }

// Update Position based on physics
    olc::vf2d moveDirection = getDirection();
    float dot   = moveDirection.x * dir.x + moveDirection.y * dir.y;
    if(thrusting)
        setDirection(moveDirection + (dir - moveDirection)*deltaTime);
    
    moveVelocity += dot * shipEngine.acceleration;
    
// Update Position based on Screen-Borders
    updatePosition(deltaTime);

// Check if there is data to be returned
    if(ret->size() <= 0) {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

void Ship::onDraw(olc::PixelGameEngine* pge) {
    pge->SetDrawTarget(layer_ship);
    SpaceObj::draw([this](Transform* tr) {
        Global::pge->DrawPartialRotatedDecal(
            tr->pos, decShip, tr->ang,  
            {sprShip->height / 2.0f, sprShip->height / 2.0f},
            {(1-thrusting)*32.0f, 0}, {(float)sprShip->height, (float)sprShip->height}
        );
        
        for(auto upgrade : upgrades)
            upgrade->draw(Global::pge, *tr);
    });
    pge->SetDrawTarget(nullptr);

    int barheight = (int)((stats->generator / stats->generatorcapacity) * 164.0f);

    olc::Pixel c = stats->generatorhalt ? olc::RED : olc::WHITE;
    c.a = 128;

    pge->FillRect(240, 28 + (164 - barheight), 16, barheight, c) ;
    pge->FillRect(240, 192, 16, barheight, c) ;

#ifdef DEBUG_BUILD
    olc::vf2d moveDirection = getDirection();
    pge->DrawLine(pos, pos+moveDirection*16.0f, olc::BLUE);
    pge->DrawLine(pos, pos+dir*28.0f, olc::GREEN);
#endif

    selectableComponents.clear();
    olc::vf2d pos(20, 40);
    for(int a = 0; a < components.size(); a++) {
        if(components.at(a)->drawShipComponent(
            stats, this, pge, pos
        )) {
            selectableComponents.push_back(a);
            pos.y += 12;
        }
    }

    int sz = selectableComponents.size();
    selectedComponent = sz < selectedComponent ? sz : selectedComponent;

    if(sz > 0)
        pge->FillRect({8, 40 + (10 * selectedComponent)}, {8, 8}, olc::RED);

}

bool Ship::shieldIsActive() {
    return currentShield != nullptr;
}

olc::Sprite* Ship::getSprite() { return sprDissolve; }
