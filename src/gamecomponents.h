#pragma once
#include <vector>

#include "./engine/physics/Collision.h"

class Ship;
class ShipUpgrade_Shield;
class Bullet;

using namespace RGNDS;

class ShipShieldDeflectable {
    public:
        virtual void gotDeflected(Ship*, ShipUpgrade_Shield*, Physics::Collision*) = 0;
        virtual std::vector<Physics::Collision::Circle> getColliders() = 0;
};

class PlayerKiller {
    public:
        virtual std::vector<Physics::Collision::Circle> getColliders() = 0;
};

class BulletHitable {
public:
    virtual std::vector<Physics::Collision::Circle> getColliders() = 0;
    virtual void hitByBullet(Bullet*, Physics::Collision*) = 0;
    virtual int getDestructionScore() = 0;
};
