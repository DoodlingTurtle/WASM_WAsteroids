#pragma once

#include "./ship_component.h"
#include "./shipstats.h"
#include "../ship.h"

class UpgradeBulletHell : public ShipComponent {
public:

    UpgradeBulletHell();
    ~UpgradeBulletHell();

    bool invokeShipComponent(ShipStats*, Ship*) override;
    bool updateShipComponent(float deltaTime) override;

    bool drawShipComponent(ShipStats* stats, Ship* ship, olc::PixelGameEngine* pge, olc::vf2d componentListIconCoordinates) override;


private:
    bool draw;
    static int instances;

};

