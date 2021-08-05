#ifndef __ShipUpgrade_H__
#define __ShipUpgrade_H__

#include "shipstats.h"
#include <vector>
#include "../../spaceobj.h"

class Ship;

class ShipUpgrade {
public:
    virtual ~ShipUpgrade(){};

    virtual bool init(ShipStats* shipstats) = 0;
    virtual void draw(olc::PixelGameEngine*, RGNDS::Transform& ship) = 0;
    virtual bool update(
            ShipStats* shipstats, Ship* ship 
          , float deltaTime
          , std::vector<SpaceObj*>* newSpaceObjects
    ) = 0;

};

#endif
