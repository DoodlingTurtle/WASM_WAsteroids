#pragma once

#include <SDL/SDL_mixer.h>

#include "../../engine/Transform.h"
#include "../../engine/physics/Collision.h"

#include "../asteroids.h"
#include "../ship.h"

#include "./shipstats.h"
#include "./shipupgrade.h"

using namespace RGNDS;

class ShipUpgrade_Shield: public ShipUpgrade 
{
public:
    ShipUpgrade_Shield();
    ~ShipUpgrade_Shield();

    bool init() override;

    void draw(olc::PixelGameEngine*, Transform& ship) override;
    bool update( Ship* ship , float deltaTime ) override;

    virtual float getRadius();

    void gotHit( Asteroid*, Ship* s, Physics::Collision*);

    static void init(olc::PixelGameEngine* pge);
    static void deinit();

private:
    float lifetime;
    float lastHitTime;
    double ang; 
    float rotspeed;
};
