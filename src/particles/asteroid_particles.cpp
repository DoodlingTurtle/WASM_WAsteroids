#include "./asteroid_particles.h"
#include "config.h"

/*#############################################################################
 * AsteroidExplosion
 *###########################################################################*/
AsteroidExplosion::AsteroidExplosion(Asteroid* ast)
: SpriteDissolve(ast->getSprite(), ast, 16.0f, 1.0f)
, GameObject({
    GameObject::SPACE_OBJ_DRAW,
    GameObject::SPACE_OBJ_UPDATE
})
, SpaceObj(64)
{}


void AsteroidExplosion::onEmitterFinished() { GameObject::assignAttribute(GameObject::DEAD); }

std::vector<SpaceObj*>* AsteroidExplosion::onUpdate(float deltaTime) { 
    SpriteDissolve::onUpdate(deltaTime);
    return nullptr;
}

void AsteroidExplosion::onDraw(olc::PixelGameEngine* pge) 
{ 
    pge->SetDrawTarget(layer_particles);
    SpriteDissolve::onDraw(pge); 
    pge->SetDrawTarget(nullptr);
}

