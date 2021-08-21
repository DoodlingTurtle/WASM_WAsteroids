#include "./asteroid_particles.h"
#include "config.h"

/*#############################################################################
 * AsteroidExplosion
 *###########################################################################*/
AsteroidExplosion::AsteroidExplosion(Asteroid* ast)
: SpriteDissolve(ast->getSprite(), ast, 16.0f, 1.0f)
, SpaceObj(64)
{}


void AsteroidExplosion::onEmitterFinished() { GameObject::assignAttribute(GameObject::DEAD); }

void AsteroidExplosion::onUpdate(float deltaTime) { SpriteDissolve::onUpdate(deltaTime); }

void AsteroidExplosion::onDraw(olc::PixelGameEngine* pge) 
{ 
    pge->SetDrawTarget(layer_particles);
    SpriteDissolve::onDraw(pge); 
    pge->SetDrawTarget(nullptr);
}

