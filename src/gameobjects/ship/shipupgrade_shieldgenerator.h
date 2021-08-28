#ifndef __ShipUpgrade_ShieldGenerator_H__
#define __ShipUpgrade_ShieldGenerator_H__

#include "../../engine/Transform.h"

#include "./shipstats.h"
#include "./ship_component.h"
#include "./shipupgrade_shield.h"

using namespace RGNDS;

class ShipUpgrade_ShieldGenerator : public ShipComponent {
public:
    ShipUpgrade_ShieldGenerator(ShipUpgrade_ShieldGenerator* = nullptr);
    virtual ~ShipUpgrade_ShieldGenerator();

    bool invokeShipComponent(ShipStats*, Ship*) override;    
    bool updateShipComponent(float deltaTime) override;
    
    bool drawShipComponent(ShipStats* stats, Ship* ship, olc::PixelGameEngine* pge, olc::vf2d componentListIconCoordinates) override; 

private:
    static bool draw;
    static int cntInstances; 
};

#endif
