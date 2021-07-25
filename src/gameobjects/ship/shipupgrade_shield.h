#ifndef __ShipUpgrade_Shield_H__
#define __ShipUpgrade_Shield_H__

#include "../../transform.h"

#include "shipstats.h"
#include "shipupgrade.h"

class Ship;

class ShipUpgrade_Shield: public ShipUpgrade 
{
public:
    ShipUpgrade_Shield();
    ~ShipUpgrade_Shield();

    bool init(ShipStats *shipstats, int* controls);
    void draw(RGNDS::Transform& ship);
    bool update(ShipStats* shipstats, Ship* ship, float deltaTime, int keys_held, int keys_up, int keys_justpressed);

    virtual float getRadius();

    void gotHit();

//    RGNDS::GL2D::PolyShape* circle;

//    glImage* gfx;

private:
    float lifetime;

    float lastHitTime;

};

#endif
