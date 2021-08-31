#pragma once

#include "./MultiUseUpgrade.h"
#include "./shipstats.h"
#include "../ship.h"

class UpgradeBulletHell : public MultiUseUpgrade {
public:
    UpgradeBulletHell();

    bool invokeShipComponent(ShipStats*, Ship*) override;

    bool drawShipComponent(ShipStats* stats, Ship* ship, olc::PixelGameEngine* pge, olc::vf2d componentListIconCoordinates) override;
};

