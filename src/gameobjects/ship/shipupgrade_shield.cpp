#include "./shipupgrade_shield.h"
#include "./shipstats.h"

#include "../../config.h"
#include "../../engine/Assets.h"

using namespace RGNDS;

// Init statics
void ShipUpgrade_Shield::init(olc::PixelGameEngine* pge) {}
void ShipUpgrade_Shield::deinit() { } 

// constructors
ShipUpgrade_Shield::ShipUpgrade_Shield() : ang(0.0f), rotspeed(PI2 * 4.0f) { }
ShipUpgrade_Shield::~ShipUpgrade_Shield() { }

// Implement Ship_Upgrade
bool ShipUpgrade_Shield::init(){
    
    lifetime = 5000.0f;
    lastHitTime = 0;
    ang = 0.0f;

    return true; 
}

bool ShipUpgrade_Shield::update(
            Ship* ship 
          , float dt
) {
    lifetime -= dt * 1000.0f;
    if(lastHitTime > 0.0f) {
        lastHitTime -= dt * 1000.0f;
        if(lastHitTime < 0)
            lastHitTime = 0;
    }

    ang += rotspeed * dt;
    if(ang > PI2)
        ang = ang - PI2;

    return (lifetime > 0.0f);
}

void ShipUpgrade_Shield::draw(
        olc::PixelGameEngine* pge, 
        Transform& ship
) {
    unsigned char r=8, g=31, b=31;

    olc::Pixel tint(255, 255, 255, 178);

    pge->DrawPartialRotatedDecal(
        ship.pos, Assets::shields->Decal(), 
        ang, {37, 37},
        {0, 0}, {74.0f, 74.0f}, {0.66f, 0.66f}, tint
    );
}

// Methods
void ShipUpgrade_Shield::gotHit( Asteroid* a, Ship* s, Physics::Collision* c) {

    // Get needed variables
    olc::vf2d invHit = c->overlapDir * (-1.0f);
    olc::vf2d aDir = a->getDirection();
    olc::vf2d sDir = s->getDirection();

    float dot = aDir.x * invHit.x + aDir.y * invHit.y;
    float dotSA = aDir.x * sDir.x + aDir.y * sDir.y; 
    float aVel = a->moveVelocity;

    // move Asteroid to the exact intersection point
    a->movePixelDistance(c->C2COverlapImpact);
  
    // set Asteroids direction to the hit direction
    a->setDirection(invHit);

    // calculate new velocity
    a->moveVelocity *= 0.90;                    // remove 10% of the velocity (because impact to the ship)
    a->moveVelocity += s->moveVelocity * dotSA; // Add ships velocity according to Dot product / influence 

    this->lastHitTime = 1000.0f;

    Mix_PlayChannel(-1, Assets::shieldBump, 0);
}

float ShipUpgrade_Shield::getRadius() {
    return 22.0f;
}
