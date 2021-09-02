#ifndef __ShipUpgrade_H__
#define __ShipUpgrade_H__

#include <vector>
#include "../../engine/Transform.h"

#include "./shipstats.h"

class Ship;

class ShipUpgrade {
public:
    virtual ~ShipUpgrade(){};

    virtual bool init() = 0;
    virtual void draw(olc::PixelGameEngine*, RGNDS::Transform& ship) = 0;
    virtual bool update( Ship* ship , float deltaTime ) = 0;

};

#endif
