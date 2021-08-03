#include "ship_explosion.h"
#include "../config.h"

/*#############################################################################
 * ShipExplosion
 *###########################################################################*/
ShipExplosion::ShipExplosion(int x, int y, olc::vf2d vel, float speed)
: t_ShipExplosion(
        new ShipExplosion_Emitter(x, y, this, vel, speed),
        new ShipExplosion_Particle()
) ,SpaceObj(64)
{ 
    bIsAlive = true; 
    spawnNewParticles(64);
}

std::vector<SpaceObj*>* ShipExplosion::onUpdate(float deltaTime) { 
    emitter->updateEmitter(deltaTime);
    return nullptr;
}

void ShipExplosion::onDraw(olc::PixelGameEngine* pge) { emitter->drawParticles(pge); }

/*#############################################################################
 * ShipExplosion_Emitter
 *###########################################################################*/
ShipExplosion_Emitter::ShipExplosion_Emitter(int x, int y, SpaceObj* exp, olc::vf2d vel, float speed)
    : t_ShipExplosion_Emitter(0, 0, 1.0f, exp) 
    , lifetime(1.0f)
{ 
    pos = vel;
    directionFromPositionVector();
    pos.x = x;
    pos.y = y;

    velocity = speed;
}

void ShipExplosion_Emitter::onEmitterUpdate(float deltaTime) {
    lifetime -= deltaTime * 0.025f;
    if(lifetime < 0.0f) lifetime = 0.0f;

    moveInDirection(deltaTime * velocity);
    velocity *= lifetime;
}


/*#############################################################################
 * ShipExplosion_Particle
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


ShipExplosion_Particle* ShipExplosion_Particle::spawnNewParticle(t_ShipExplosion_Emitter* em){

    ShipExplosion_Particle* p = new ShipExplosion_Particle(em);

    p->pos.x = ((RandF() * 32.0f) - 16.0f) * 0.75f;
    p->pos.y = ((RandF() * 32.0f) - 16.0f) * 0.75f;
    p->directionFromPositionVector();
    p->lifetime = 1500 + RandF()*500;

    return p;
}

ShipExplosion_Particle::ShipExplosion_Particle() 
:ShipExplosion_Particle(nullptr)
{}

ShipExplosion_Particle::ShipExplosion_Particle(t_ShipExplosion_Emitter* em) 
{ this->em = em; }

bool ShipExplosion_Particle::onParticleUpdate(float deltaTime) {
    lifetime -= deltaTime * 1000.0;
    if(lifetime <= 0) return false;

    moveInDirection(3 * deltaTime);
    return true;
}

void ShipExplosion_Particle::onParticleDraw(olc::PixelGameEngine* pge){
    pge->DrawDecal(em->pos + pos, decal);  
};
