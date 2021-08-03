#include "ship_explosion.h"
#include "../config.h"

/*#############################################################################
 * ShipExplosion
 *###########################################################################*/
ShipExplosion::ShipExplosion(int x, int y)
: ParticleSystem<ShipExplosion_Emitter, ShipExplosion_Particle>(
        new ShipExplosion_Emitter(x, y, 1.0f, this),
        new ShipExplosion_Particle()
) ,SpaceObj(64)
{ bIsAlive = true; }


/*#############################################################################
 * Ship_Explosion
 *###########################################################################*/

olc::Sprite* ShipExplosion_Particle::sprite = nullptr;
olc::Decal*  ShipExplosion_Particle::decal = nullptr;
bool ShipExplosion_Particle::initDone = false;

void ShipExplosion_Particle::init(olc::PixelGameEngine* pge) {
    if(initDone) return;

    sprite = new olc::Sprite(2, 2);
    pge->SetDrawTarget(sprite);
        pge->FillRect(0, 0, 2, 2, olc::RED);
    pge->SetDrawTarget(nullptr);

    decal = new olc::Decal(sprite);

    initDone=true;
}
void ShipExplosion_Particle::deinit() {
    delete sprite;
    delete decal;
    initDone = false;
}


ShipExplosion_Particle* ShipExplosion_Particle::spawnNewParticle(ShipExplosion_Emitter* em){

    ShipExplosion_Particle* p = new ShipExplosion_Particle(em);

    p->pos.x = ((RandF() * 56.0f) - 28.0f);
    p->pos.y = ((RandF() * 56.0f) - 28.0f);
    p->directionFromPositionVector();
    p->lifetime = 1500 + RandF()*500;

    return p;

}

ShipExplosion_Particle::ShipExplosion_Particle() 
:ShipExplosion_Particle(nullptr)
{}

ShipExplosion_Particle::ShipExplosion_Particle(ShipExplosion_Emitter* em) 
{ this->em = em; }

bool ShipExplosion_Particle::onParticleUpdate(float deltaTime) {
    lifetime -= deltaTime * 1000.0;
    if(lifetime <= 0) return false;

    moveInDirection(6 * deltaTime);
    return true;
}

void ShipExplosion_Particle::onParticleDraw(olc::PixelGameEngine* pge){
    pge->DrawDecal(em->pos + pos, decal);  
};
