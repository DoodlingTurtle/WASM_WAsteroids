#include "asteroid_particles.h"
#include "../config.h"

/*#############################################################################
 * AsteroidExplosion
 *###########################################################################*/
AsteroidExplosion::AsteroidExplosion(Asteroids::Asteroid* ast)
: SpriteDissolve(ast->getSprite(), ast, 16.0f, 1.0f)
, SpaceObj(64)
{ SpaceObj::bIsAlive = true; }


void AsteroidExplosion::onEmitterFinished() { SpaceObj::kill(); }

std::vector<SpaceObj*>* AsteroidExplosion::onUpdate(float deltaTime) { 
    SpriteDissolve::onUpdate(deltaTime);
    return nullptr;
}

void AsteroidExplosion::onDraw(olc::PixelGameEngine* pge) 
{ SpriteDissolve::onDraw(pge); }

bool AsteroidExplosion::allowDeleteAfterDeath() { 
    return true; }


