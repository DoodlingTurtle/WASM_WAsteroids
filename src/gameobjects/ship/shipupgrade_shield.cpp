#include "shipupgrade_shield.h"
#include "shipstats.h"
#include "../../config.h"

// Init statics
olc::Sprite* ShipUpgrade_Shield::sprite = nullptr;
olc::Decal*  ShipUpgrade_Shield::decal = nullptr;
Mix_Chunk*   ShipUpgrade_Shield::sfxBump = nullptr;

void ShipUpgrade_Shield::init(olc::PixelGameEngine* pge) {
    sprite = new olc::Sprite("assets/sprites/shield.png");
    decal = new olc::Decal(sprite);
    sfxBump = Mix_LoadWAV("assets/sfx/sci-fi_sounds/laserLarge_002.ogg");
}
void ShipUpgrade_Shield::deinit() {
    if(decal != nullptr)    delete decal;
    if(sprite != nullptr)   delete sprite;
    if(sfxBump != nullptr)  delete sfxBump;
}

// constructors
ShipUpgrade_Shield::ShipUpgrade_Shield() {
    rotspeed = PI2 * 4.0f;
    ang = 0.0f;
}
ShipUpgrade_Shield::~ShipUpgrade_Shield() { }

// Implement Ship_Upgrade
bool ShipUpgrade_Shield::init(ShipStats* shipstats){
    
    lifetime = 5000.0f;
    lastHitTime = 0;
    ang = 0.0f;

    return true; 
}

bool ShipUpgrade_Shield::update(
            ShipStats* shipstats, Ship* ship 
          , float dt
          , std::vector<SpaceObj*>* newSpaceObjects
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
        RGNDS::Transform& ship
) {
    unsigned char r=8, g=31, b=31;

    olc::Pixel tint(255, 255, 255, 178);

    pge->DrawPartialRotatedDecal(
        ship.pos, decal, 
        ang, {37, 37},
        {0, 0}, {(float)sprite->height, (float)sprite->height}, {0.66f, 0.66f}, tint
    );
}

// Methods
void ShipUpgrade_Shield::gotHit( Asteroids::Asteroid* a, Ship* s, RGNDS::Collision* c) {
    Debug("Bump: " << c->overlapDir.x << " " << c->overlapDir.y);

    a->setDirection(c->overlapDir);

    this->lastHitTime = 1000.0f;

    Mix_PlayChannel(-1, sfxBump, 0);
}

float ShipUpgrade_Shield::getRadius() {
    return 22.0f;
}
