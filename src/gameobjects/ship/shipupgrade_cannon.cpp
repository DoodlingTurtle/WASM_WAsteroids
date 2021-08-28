#include "./shipupgrade_cannon.h"
#include "../../engine/Global.h"
#include "../../engine/Assets.h"

ShipUpgrade_Cannon::ShipUpgrade_Cannon() {}
ShipUpgrade_Cannon::~ShipUpgrade_Cannon() { }

using namespace RGNDS;

bool ShipUpgrade_Cannon::init(ShipStats* stats) { return true; }

bool ShipUpgrade_Cannon::update(
        ShipStats* stats, Ship* ship 
      , float deltaTime
) {
    if(Global::input.pressed&KEYPAD_R) {
        if(!stats->generatorhalt && stats->generator >= stats->shotenergyconsumption) {

            Bullet* b = stats->prototypeBullet->clone(ship->pos, ship->dir, std::max(0.0f, ship->moveVelocity * (ship->dir.dot(ship->getDirection()))));
            b->movePixelDistance(16);
            Global::world.addGameObject(b);
            stats->generator -= stats->shotenergyconsumption;

            Mix_PlayChannel(-1, Assets::bullet_fire_1, 0);
        }
    } 
    return true;
}

void ShipUpgrade_Cannon::draw(olc::PixelGameEngine*, Transform& ship) {}
