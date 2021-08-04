#include "ship.h"
#include <math.h>
#include <stdio.h>

#include "../config.h"
#include "../global.h"
#include "../collision.h"

#define SHIP_DEFAULT_RADIUS 16.0f

Ship::Ship() 
: SpaceObj(SHIP_DEFAULT_RADIUS)
  , angRes(PI)
  , thrusting(false)
  , shieldIsUp(false)
  , sprShip(nullptr)
  , decShip(nullptr)
{
    /*TODO: redo all audio
    mmLoadEffect(SFX_SFX_LASER1);
    mmLoadEffect(SFX_S_EXP);
    mmLoadEffect(SFX_S_THRUST);
    */

    sprDissolve = new olc::Sprite(32, 32);
    sprShip = new olc::Sprite("./assets/ship.png");
    decShip = new olc::Decal(sprShip);    

    Global::pge->SetDrawTarget(sprDissolve);
    Global::pge->DrawPartialSprite({ 0, 0 }, sprShip, { 32, 0 }, { 32, 32 });
    Global::pge->SetDrawTarget(nullptr);

    this->bIsAlive = true;

    stats = Global::shipStats;

    reset();
}

Ship::~Ship() 
{
    Debug("Delete ship dissolveSpr");
    delete sprDissolve;
    Debug("Delete ship spr");
    delete sprShip;
    Debug("Delete ship dec");
    delete decShip;

    Debug("Kill shots");
    shots.killall();

    Debug("clear upgrades");
    clearUpgrades();
    /*
    mmUnloadEffect(SFX_SFX_LASER1);
    mmUnloadEffect(SFX_S_EXP);
    mmUnloadEffect(SFX_S_THRUST);
    */
}

void Ship::clearUpgrades() 
{
    currentShield = nullptr;
    upgrades.clear();
    newUpgrades.clear();
}

void Ship::addUpgrade(ShipUpgrade *upgrade) {

    if(upgrade->init(stats))
        upgrades.push_back(upgrade);

    // If upgrade is instanceOf ShipUpgrade_Shield, the register as currentShield
    ShipUpgrade_Shield* shieldPtr = dynamic_cast<ShipUpgrade_Shield*>(upgrade);
    if(shieldPtr != nullptr)
        currentShield = shieldPtr;
}


void Ship::reset() 
{
    Debug("ship reset");
    pos.x = APP_SCREEN_WIDTH/2;
    pos.y = APP_SCREEN_HEIGHT/4;
    
    scale = 1;
    setAngleRel(PI/2);
    velocity.x = 0;
    velocity.y = 0;
    bIsAlive = true;

    clearUpgrades();

    addUpgrade(&shieldgenerator);

    objRadius = 24;
    stats->generator = stats->generatorcapacity;

}

RGNDS::Collision::Circle Ship::getCollider() {
    return {pos.x, pos.y, 14.0f*scale};
}

std::vector<SpaceObj*>* Ship::onUpdate(float deltaTime) {
//check asteroids collision
    if(RGNDS::Collision::checkCircleOnCircle(
        getCollider(), 
        Global::asteroids->getActiveColliders()
    )){
        this->kill();
        return nullptr;
    }; 

//TODO: Redo Controlls
    std::vector<SpaceObj*>* ret = nullptr;

    if(Global::pge->GetKey(Global::gamecontrols[GAMEINPUT_FIRE]).bPressed) {
        if(!stats->generatorhalt && stats->generator >= stats->shotenergyconsumption) {
            Shots::Shot* s = shots.spawnShot(ang, &pos);
            ret = new std::vector<SpaceObj*>();
            ret->push_back(s);
            stats->generator -= stats->shotenergyconsumption;
        }
    } 
    if(Global::pge->GetKey(Global::gamecontrols[GAMEINPUT_TURNRIGHT]).bHeld)
        setAngleRel(angRes*deltaTime);

    if(Global::pge->GetKey(Global::gamecontrols[GAMEINPUT_TURNLEFT]).bHeld)
        setAngleRel(-angRes*deltaTime);

    thrusting = false;
    bool allowgeneratoregen = true;
    if(Global::pge->GetKey(Global::gamecontrols[GAMEINPUT_ACCELERATE]).bHeld) {
        float consumption = stats->thrustenergyconsumption * deltaTime;
        if(!stats->generatorhalt && stats->generator >= consumption) {
            thrusting = true;
            stats->generator -= consumption;
        }
        else allowgeneratoregen = false;
        /*TODO: Redo sound
         * if(thrust_sound == 0) {
            thrustSoundTimer  = 0.00;
            thrust_sound = mmEffect(SFX_S_THRUST);
        }
        else {
            thrustSoundTimer += 1000.0f * deltaTime;
            if(thrustSoundTimer >= 1000) {
                thrustSoundTimer = 0;
                mmEffectCancel(thrust_sound);
                thrust_sound = mmEffect(SFX_S_THRUST);
            }
        }
        */
    }
    else {
        //mmEffectCancel(thrust_sound);
        //thrust_sound = 0;

    } 
    
    if(thrusting) 
        shipEngine.accelerate(deltaTime * 15.0f);
    else
        shipEngine.decerlerate(1);

    if(stats->generator <= stats->generatorlock)
        stats->generatorhalt = true;

    if(stats->generator >= stats->generatorunlock)
        stats->generatorhalt = false;

// Activate new upgrades
    for(int a = 0; a < newUpgrades.size(); a++)
        upgrades.push_back(newUpgrades.at(a));

    newUpgrades.clear();
// Genrator Recovery
    if(allowgeneratoregen) {
        stats->generator += deltaTime * stats->generatorrecovery;
        if(stats->generator > stats->generatorcapacity)
            stats->generator = stats->generatorcapacity;
    }

// Update upgrades
    ShipUpgrade* upgrade;
    for(int a = upgrades.size()-1; a >= 0; a--) {
        upgrade = upgrades.at(a);
        if(!upgrade->update(stats, this, deltaTime)) {
            Debug("remove ship upgrage " << upgrade);
            
            if(upgrade == currentShield) {
                currentShield = nullptr;
                objRadius = SHIP_DEFAULT_RADIUS;
            }

            upgrades.erase(upgrades.begin()+a);
        }
    }

// Update Position based on physics
    velocity += dir * shipEngine.acceleration;
    
// Update Position based on Screen-Borders
    updatePosition(deltaTime);

    return ret;
}

void Ship::onDraw(olc::PixelGameEngine* pge) 
{
    pge->SetDrawTarget(layer_ship);
    SpaceObj::draw([this](Transform* tr) {
        Global::pge->DrawPartialRotatedDecal(
            tr->pos, decShip, tr->ang,  
            {sprShip->height / 2.0f, sprShip->height / 2.0f},
            {(1-thrusting)*32.0f, 0}, {(float)sprShip->height, (float)sprShip->height}
        );
    });
    pge->SetDrawTarget(nullptr);

    int barheight = (int)((stats->generator / stats->generatorcapacity) * 164.0f);

    olc::Pixel c = stats->generatorhalt ? olc::RED : olc::WHITE;

    pge->FillRect(240, 28 + (164 - barheight), 16, barheight, c) ;
    pge->FillRect(240, 192, 16, barheight, c) ;
}

bool Ship::shieldIsActive() {
    return currentShield != nullptr;
}

olc::vf2d Ship::getPassiveVelocity() { return this->velocity; }
float     Ship::getTravelDistance(float deltaTime) { 
    return sqrt(velocity.x * velocity.x + velocity.y * velocity.y); 
}


olc::Sprite* Ship::getSprite() { return sprDissolve; }
