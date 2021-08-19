#include "./ship_explosion.h"

/*#############################################################################
 * ShipExplosion
 *###########################################################################*/
ShipExplosion::ShipExplosion(Ship* ship)
: SpaceObj(64.0f)
, SpriteDissolve(ship->getSprite(), ship, 16.0f, 1.5f)
{ this->bIsAlive = true; }

void ShipExplosion::onEmitterFinished() {
    this->kill();
}

// Implement SpaceOb
std::vector<SpaceObj*>* ShipExplosion::onUpdate(float deltaTime)
{ SpriteDissolve::onUpdate(deltaTime); return nullptr; }

void ShipExplosion::onDraw(olc::PixelGameEngine* pge) 
{ SpriteDissolve::onDraw(pge); }

bool ShipExplosion::allowDeleteAfterDeath() { return false; }
