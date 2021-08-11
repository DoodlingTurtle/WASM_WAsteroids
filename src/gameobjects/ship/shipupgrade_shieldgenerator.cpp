#include "shipupgrade_shieldgenerator.h"
#include "../ship.h"
#include "shipupgrade_shield.h"

#include "../../config.h"

bool ShipUpgrade_ShieldGenerator::draw = true;
int  ShipUpgrade_ShieldGenerator::cntInstances = 0;

ShipUpgrade_ShieldGenerator::ShipUpgrade_ShieldGenerator( ShipUpgrade_ShieldGenerator* ) { cntInstances++; }
ShipUpgrade_ShieldGenerator::~ShipUpgrade_ShieldGenerator() { cntInstances--; }

bool ShipUpgrade_ShieldGenerator::invokeShipComponent(
        ShipStats* stats, Ship* ship, std::vector<SpaceObj*>* newSpaceObjectsToSpawn){

    ship->addUpgrade(new ShipUpgrade_Shield()); 

    return false;
};    

bool ShipUpgrade_ShieldGenerator::drawShipComponent(ShipStats* stats, Ship* ship, 
        olc::PixelGameEngine* pge, olc::vf2d coords) {
    if(!draw) return false;

    for(int a = 0; a < cntInstances; a++) {
        pge->DrawCircle(ship->pos, 4, olc::BLUE);
    }

    draw = false;


    pge->DrawStringDecal(
        { coords.x, coords.y } , "Shield", olc::WHITE, {1.0f, 1.0f});
    return true;
};

bool ShipUpgrade_ShieldGenerator::updateShipComponent(float deltaTime) { draw = true; return true; }
