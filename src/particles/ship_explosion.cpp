#include "./ship_explosion.h"

/*#############################################################################
 * ShipExplosion
 *###########################################################################*/
ShipExplosion::ShipExplosion(Ship* ship)
: GameObject({ GameObject::MAINGAME_COMPONENT })
, SpaceObj(64.0f)
, SpriteDissolve(ship->getSprite(), ship, 16.0f, 1.5f)
{}

void ShipExplosion::onEmitterFinished() 
{ assignAttribute(GameObject::DEAD); }

void ShipExplosion::onUpdate(float deltaTime)
{ SpriteDissolve::onUpdate(deltaTime); }

void ShipExplosion::onDraw(olc::PixelGameEngine* pge) 
{ SpriteDissolve::onDraw(pge); }

