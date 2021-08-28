#include "./ship.h"

#include <math.h>
#include <stdio.h>

#include "../config.h"
#include "../engine/Global.h"
#include "../engine/physics/Collision.h"
#include "../engine/Assets.h"

#include "./ship/shipupgrade_shield.h"
#include "./ship/shipupgrade_cannon.h"

#include "../particles/ship_explosion.h"

#define SHIP_MAX_VELOCITY 256.0f
#define SHIP_DEFAULT_RADIUS 16.0f

using namespace RGNDS;

Ship::Ship() 
: GameObject({
    GameObject::PLAYER_SHIP,
    GameObject::MAINGAME_COMPONENT
})
  , SpaceObj(SHIP_DEFAULT_RADIUS)
  , angRes(PI)
  , thrusting(false)
  , chaThrust(-1)
  , selectedComponent(0)
{
    sprDissolve = new olc::Sprite(32, 32);
    Global::game->SetDrawTarget(sprDissolve);
    Global::game->DrawPartialSprite({ 0, 0 }, Assets::ship->Sprite(), { 32, 0 }, { 32, 32 });
    Global::game->SetDrawTarget(nullptr);

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

    clearUpgrades();

    if(chaThrust != -1) {
        Mix_HaltChannel(chaThrust);
        chaThrust = -1;
    }

    delete sprDissolve;
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
    pos.x = Global::layout->app_width/2;
    pos.y = Global::layout->app_height/2;
    
    scale = 1;
    setAngleRel(PI/2);
    SpaceObj::setDirection(olc::vf2d((float)cos(PI/2), (float)sin(PI/2)));
    moveVelocity = 0.0f;
    setDirection({0.0f, 0.0f});

    clearUpgrades();
    
    objRadius = 24;
    stats->generator = stats->generatorcapacity;

}

Physics::Collision::Circle Ship::getCollider() {
    float radius = 14.0f;

    if(currentShield != nullptr)
        radius = currentShield->getRadius();

    return {pos.x, pos.y, radius * scale};
}

void Ship::onUpdate(float deltaTime) {

//check asteroids collision
//TODO: change to ship_killer

    if (currentShield) {
        auto list = Global::world->allShipShieldDeflectable();
        Physics::Collision c;
        for(auto go : list)
            if (Physics::Collision::checkCircleOnCircle(
                getCollider(),
                go->getColliders(),
                &c
            )) {
                Mix_PlayChannel(-1, Assets::shieldBump, 0);
                go->gotDeflected(this, currentShield, &c);
            }
    }
    else {
        auto list = Global::world->allPlayerKiller();
        for (auto go : list)
            if (Physics::Collision::checkCircleOnCircle(
                getCollider(),
                go->getColliders()
            )) {
                Mix_PlayChannel(-1, Assets::shipExplode, 0);
                Global::world->addGameObject(new ShipExplosion(this));
                assignAttribute(GameObject::DEAD);
                return;
            }
    }
    

    // Input Rotation
    if(Global::input->held&KEYPAD_RIGHT) setAngleRel(angRes*deltaTime); 
    if(Global::input->held&KEYPAD_LEFT) setAngleRel(-angRes*deltaTime); 

    // Input Component selection
    if(Global::input->pressed&KEYPAD_X) selectedComponent--;
    if(Global::input->pressed&KEYPAD_Y) selectedComponent++;

    int sz = selectableComponents.size()-1;
    if(selectedComponent < 0)   selectedComponent = 0;
    if(selectedComponent > sz)  selectedComponent = sz; 

    // Activate component with A-Key (P on the Keybaord)
    if(sz > -1 && Global::input->pressed&KEYPAD_A) {
        int index = selectableComponents.at(selectedComponent);
        ShipComponent* c = components.at(index);
        if(c) {
            if(!c->invokeShipComponent(stats, this)) {
                delete c;
                c = nullptr;
            }
        }
        if(!c) components.erase(components.begin()+index);
    }


    // Input Thrusting
    thrusting = false;
    bool allowgeneratoregen = true;
    if(Global::input->held&KEYPAD_UP) {
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
            chaThrust = Mix_PlayChannel(-1, Assets::shipThrust, -1);
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
        if(!upgrade->update(stats, this, deltaTime)) {
            if(upgrade == currentShield) {
                currentShield = nullptr;
            }
            Debug("remove ship upgrade " << upgrade);
            delete upgrade;

            upgrades.erase(upgrades.begin()+a);
        }
    }

// Update Position based on physics
    olc::vf2d moveDirection = getDirection();
    float dot   = moveDirection.x * dir.x + moveDirection.y * dir.y;
    if (thrusting) {
        setDirection(moveDirection + (dir - moveDirection) * deltaTime);
        moveVelocity += dot * shipEngine.acceleration;
        moveVelocity = std::max(std::min(moveVelocity, SHIP_MAX_VELOCITY), -SHIP_MAX_VELOCITY);
    }
    
// Update Position based on Screen-Borders
    updatePosition(deltaTime);
}

void Ship::onDraw(olc::PixelGameEngine* pge) {
    pge->SetDrawTarget(layer_ship);
    SpaceObj::draw([this](Transform* tr) {
        Global::game->DrawPartialRotatedDecal(
            tr->pos, Assets::ship->Decal(), tr->ang,  
            {16.0f, 16.0f},
            {(1-thrusting)*32.0f, 0}, {(float)32.0f, (float)32.0f}
        );
        
        for(auto upgrade : upgrades)
            upgrade->draw(Global::game, *tr);
    });
    pge->SetDrawTarget(nullptr);

    float generator = (stats->generator / stats->generatorcapacity);

    olc::Pixel c = stats->generatorhalt ? olc::RED : olc::WHITE;
    c.a = 128;

    olc::vf2d barsize = Global::layout->ship_energy_empty_size - Global::layout->ship_energy_full_size;
    barsize.x = barsize.x * (1.0f - ((barsize.x < 0) * 2.0f));  // Make barsize absolute
    barsize.y = barsize.y * (1.0f - ((barsize.y < 0) * 2.0f));

    olc::vf2d barpos = Global::layout->ship_energy_empty_pos - Global::layout->ship_energy_full_pos;
    barpos.x = barpos.x * (1.0f - ((barpos.x < 0) * 2.0f));  // Make barpos absolute
    barpos.y = barpos.y * (1.0f - ((barpos.y < 0) * 2.0f));


    pge->FillRectDecal(
          Global::layout->ship_energy_empty_pos  - barpos  * generator
        , Global::layout->ship_energy_empty_size + barsize * generator
      , c
    );

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

bool Ship::shieldIsActive() { return currentShield != nullptr; }
olc::Sprite* Ship::getSprite() { return sprDissolve; }

