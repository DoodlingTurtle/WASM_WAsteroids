#include "shipupgrade_cannon.h"
#include "../../global.h"

ShipUpgrade_Cannon::ShipUpgrade_Cannon() {}
ShipUpgrade_Cannon::~ShipUpgrade_Cannon() {
    shots.killall();
}

bool ShipUpgrade_Cannon::init(ShipStats* stats) { return true; }

bool ShipUpgrade_Cannon::update(
        ShipStats* stats, Ship* ship 
      , float deltaTime
      , std::vector<SpaceObj*>* ret
) {
    if(Global::pge->GetKey(Global::gamecontrols[GAMEINPUT_FIRE]).bPressed) {
        if(!stats->generatorhalt && stats->generator >= stats->shotenergyconsumption) {
            Shots::Shot* s = shots.spawnShot(ship->ang, &(ship->pos));
            ret->push_back(s);
            stats->generator -= stats->shotenergyconsumption;
        }
    } 
    return true;
}

void ShipUpgrade_Cannon::draw(olc::PixelGameEngine*, RGNDS::Transform& ship) {}
