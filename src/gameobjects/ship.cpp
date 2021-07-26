#include "ship.h"
#include <math.h>
#include <stdio.h>

#include "../config.h"
#include "../global.h"

#define SHIP_DEFAULT_RADIUS 16.0f

Ship::Ship() 
: SpaceObj(SHIP_DEFAULT_RADIUS)
  , angRes(PI/2)
  , thrusting(false)
  , shieldIsUp(false)
  , sprShipIdle(nullptr)
  , sprShipThrusting(nullptr)
{
    /*TODO: redo all audio
    mmLoadEffect(SFX_SFX_LASER1);
    mmLoadEffect(SFX_S_EXP);
    mmLoadEffect(SFX_S_THRUST);
    */

    olc::Sprite spr = olc::Sprite("./assets/ship.png");
    
    sprShipIdle      = new olc::Sprite(32, 32);
    sprShipThrusting = new olc::Sprite(32, 32);

    Global::pge->SetDrawTarget(sprShipThrusting);
    Global::pge->DrawPartialSprite(0, 0, &spr, 0, 0, 32, 32);
    
    Global::pge->SetDrawTarget(sprShipIdle);
    Global::pge->DrawPartialSprite(0, 0, &spr, 32, 0, 32, 32);
    
    Global::pge->SetDrawTarget(nullptr);

    this->bIsAlive = true;
    reset();
}

Ship::~Ship() 
{
    delete sprShipThrusting;
    delete sprShipIdle;

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
    std::printf("ship reset\n");
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

    //Engine_Log("Generator-Cap: " << stats->generatorcapacity);
}

std::vector<SpaceObj*>* Ship::onUpdate(float deltaTime) {
//TODO: Redo Controlls
    std::vector<SpaceObj*>* ret = nullptr;

    if(Global::pge->GetKey(Global::gamecontrols[GAMEINPUT_FIRE]).bPressed) {
        Shots::Shot* s = shots.spawnShot(ang, &pos);
        ret = new std::vector<SpaceObj*>();
        ret->push_back(s);
    } 
    if(Global::pge->GetKey(Global::gamecontrols[GAMEINPUT_TURNRIGHT]).bHeld)
        setAngleRel(angRes*deltaTime);

    if(Global::pge->GetKey(Global::gamecontrols[GAMEINPUT_TURNLEFT]).bHeld)
        setAngleRel(-angRes*deltaTime);

    if(Global::pge->GetKey(Global::gamecontrols[GAMEINPUT_ACCELERATE]).bHeld) {
        thrusting = true;
        shipEngine.accelerate(deltaTime * 10.0f);
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
        thrusting = false;
        shipEngine.decerlerate(1);
        //mmEffectCancel(thrust_sound);
        //thrust_sound = 0;

    }


// Activate new upgrades
    for(int a = 0; a < newUpgrades.size(); a++)
        upgrades.push_back(newUpgrades.at(a));

    newUpgrades.clear();

// Genrator Recovery
    stats->generator += deltaTime * stats->generatorrecovery;
    if(stats->generator > stats->generatorcapacity)
        stats->generator = stats->generatorcapacity;

// Update upgrades
    ShipUpgrade* upgrade;
    for(int a = upgrades.size()-1; a >= 0; a--) {
        upgrade = upgrades.at(a);
        if(!upgrade->update(stats, this, deltaTime)) {
            std::printf("remove ship upgrage %d\n", upgrade);
            
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
    SpaceObj::draw([this](Transform* tr) {
        
        olc::GFX2D::Transform2D tra;
        tr->toTransform2D(16, 16, &tra);


        if(this->thrusting)
            olc::GFX2D::DrawSprite(sprShipThrusting, tra); 
        else
            olc::GFX2D::DrawSprite(sprShipIdle, tra); 

        Global::pge->DrawLine(
                tr->pos.x, tr->pos.y, 
                tr->pos.x + dir.x*16, tr->pos.y + dir.y*16, 
                olc::GREEN
        );

        /*
        for(auto upgrade : upgrades) {
            upgrade->draw(*tr);
        }
        */
    });
   
    int barheight = (int)((stats->generator / stats->generatorcapacity) * 164.0f);
    //RGNDS::GL2D::glRectFilled(240, 28 + (164 - barheight), 16, barheight, 0xffff) ;
    //RGNDS::GL2D::glRectFilled(240, 192, 16, barheight, 0xffff);
}

bool Ship::shieldIsActive() {
    return currentShield != nullptr;
}

bool Ship::gotHit(SpaceObj* culprit) {
    if(currentShield != nullptr) {
        currentShield->gotHit();
        return false;
    }
    else {
        //Engine_Log("Ship " << this << " got killed by " << culprit);
        /*mmEffect(SFX_S_EXP); 
        if(thrust_sound)
            mmEffectCancel(thrust_sound);
        */
        kill(); 
        return true;
    }
}







//static float thrustSoundTimer;
//ShipExplosionParticle ShipExplosionParticle::proto = ShipExplosionParticle();

/*ShipExplosionParticle::ShipExplosionParticle() : ParticleSystem::Particle() 
{
    pos.x = Engine_RandF() * 16 - 8;
    pos.y = Engine_RandF() * 16 - 8;

    velocity = Engine_RandF() * 64+32;
    lifetime = Engine_RandF() * 1000+1000;

    directionFromPositionVector();
    
}
ShipExplosionParticle::~ShipExplosionParticle() {}

bool ShipExplosionParticle::update(float deltatime) 
{
    lifetime -= deltatime*1000.0f;
    if(lifetime <= 0) return false;

    moveInDirection(velocity*deltatime);
    velocity *= 0.90;

    return true;
}
void ShipExplosionParticle::attachToVector(float deltaTime, int index, std::vector<RGNDS::Point<double>>* vec) 
{
    RGNDS::Point<double> d;
    d.x = pos.x-1;
    d.y = pos.y-1;

    vec->push_back(d);
    
    d.x += 3;
    vec->push_back(d);
    d.x -= 3;

    d.y += 3;
    vec->push_back(d);
}
ShipExplosionParticle* ShipExplosionParticle::getNewInstance(int index) 
{
    return new ShipExplosionParticle();
}



ShipExplosion::ShipExplosion(Ship* ship) : ParticleSystem::Emitter(ship->pos.x, ship->pos.y, 20, &ShipExplosionParticle::proto)
{
    velocity.x = ship->velocity.x / 4;
    velocity.y = ship->velocity.y / 4;
    pos.x = transform.pos.x;
    pos.y = transform.pos.y;

    bIsAlive = true;



}
ShipExplosion::~ShipExplosion(){};

void ShipExplosion::onUpdate(SpaceObj::MainGameUpdateData* data)
{
    SpaceObj::updatePosition();
    transform.pos.x = pos.x;
    transform.pos.y = pos.y;

    ParticleSystem::Emitter::update(data->deltaTime);
}
void ShipExplosion::onDraw(SpaceObj::MainGameDrawData* data) 
{
    ParticleSystem::Emitter::draw(COLOR_SHIP, 31, 2);
}
void ShipExplosion::onNoParticlesLeft() { SpaceObj::kill(); }
*/

