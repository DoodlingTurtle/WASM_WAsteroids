#include "./ship_explosion.h"

/*#############################################################################
 * ShipExplosion
 *###########################################################################*/
ShipExplosion::ShipExplosion(Ship* ship)
: GameObject({
        GameObject::SPACE_OBJ_DRAW,
        GameObject::SPACE_OBJ_UPDATE,
        GameObject::MAINGAME_COMPONENT
    })
, SpaceObj(64.0f)
, SpriteDissolve(ship->getSprite(), ship, 16.0f, 1.5f)
{}

void ShipExplosion::onEmitterFinished() {
    ;
}

// Implement SpaceOb
std::vector<SpaceObj*>* ShipExplosion::onUpdate(float deltaTime)
{ SpriteDissolve::onUpdate(deltaTime); return nullptr; }

void ShipExplosion::onDraw(olc::PixelGameEngine* pge) 
{ SpriteDissolve::onDraw(pge); }

