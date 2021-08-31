#ifndef __ShipUpgrade_ShieldGenerator_H__
#define __ShipUpgrade_ShieldGenerator_H__

#include "../../engine/Transform.h"

#include "./shipstats.h"
#include "./MultiUseUpgrade.h"
#include "./shipupgrade_shield.h"

using namespace RGNDS;

class ShipUpgrade_ShieldGenerator : public MultiUseUpgrade {
public:

    ShipUpgrade_ShieldGenerator();

    bool invokeShipComponent(ShipStats*, Ship*) override;    
    bool drawShipComponent(ShipStats* stats, Ship* ship, olc::PixelGameEngine* pge, olc::vf2d componentListIconCoordinates) override; 

};

#endif
