#pragma once
#include "olcPixelGameEngine.h"

#include <vector>
#include "core/collision.h"

class Ship;
class ShipUpgrade_Shield;
class Bullet;

class WorldDrawable {
    public:
        virtual void onDraw(olc::PixelGameEngine*) = 0;
};

class WorldUpdateable {
    public:
        virtual void onUpdate(float deltaTime) = 0;
};

class ShipShieldDeflectable {
    public:
        virtual void gotDeflected(Ship*, ShipUpgrade_Shield*, RGNDS::Collision*) = 0;
        virtual std::vector<RGNDS::Collision::Circle> getColliders() = 0;
};

class PlayerKiller {
    public:
        virtual std::vector<RGNDS::Collision::Circle> getColliders() = 0;
};

class BulletHitable {
public:
    virtual std::vector<RGNDS::Collision::Circle> getColliders() = 0;
    virtual void hitByBullet(Bullet*, RGNDS::Collision*) = 0;
    virtual int  getDestructionScore() = 0;
};
