#ifndef __ShipUpgrade_H__
#define __ShipUpgrade_H__

#include "shipstats.h"

class Ship;

class ShipUpgrade {
public:
    virtual ~ShipUpgrade(){};

    virtual bool init(ShipStats* shipstats) = 0;
    virtual void draw(RGNDS::Transform& ship) = 0;
    virtual bool update(ShipStats* shipstats, Ship* ship, float deltaTime) = 0;

};

#endif
