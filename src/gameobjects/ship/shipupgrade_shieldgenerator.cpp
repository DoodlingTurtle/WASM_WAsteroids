#include "./shipupgrade_shieldgenerator.h"
#include "./shipupgrade_shield.h"

#include "gameobjects/ship.h"
#include "config.h"

ShipUpgrade_ShieldGenerator::ShipUpgrade_ShieldGenerator() : MultiUseUpgrade(0) { }

bool ShipUpgrade_ShieldGenerator::invokeShipComponent(
        ShipStats* stats, Ship* ship
){
    ship->addUpgrade(new ShipUpgrade_Shield()); 
    return false;
};    

bool ShipUpgrade_ShieldGenerator::drawShipComponent(ShipStats* stats, Ship* ship, 
        olc::PixelGameEngine* pge, olc::vf2d coords) {
    if(!allowDraw()) return false;

    int cntInstances = getInstances();

    pge->DrawCircle(ship->pos, 4, olc::BLUE);
    pge->DrawStringDecal(
        { coords.x, coords.y } , "Shield (" + std::to_string(cntInstances) + "x)", olc::WHITE, {1.0f, 1.0f});
    return true;
}

