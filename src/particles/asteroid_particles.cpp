#include "asteroid_particles.h"
#include "../config.h"

/*#############################################################################
 * Asteroid_Particle_Emitter
 *###########################################################################*/
Asteroid_Particle_Emitter::Asteroid_Particle_Emitter(int x, int y)
:SpaceObj(64)
{
    bIsAlive = true;
    pos.x = x;
    pos.y = y;
}

void Asteroid_Particle_Emitter::onParticleAssign(ParticleSystem::Particle* p) { 
    Debug("Particle Assign");
    spawnNewParticles(16); }
void Asteroid_Particle_Emitter::onNoParticlesLeft() { kill(); }

std::vector<SpaceObj*>* Asteroid_Particle_Emitter::onUpdate(float deltaTime) { 
    updateParticles(deltaTime);
    return nullptr;
}
void Asteroid_Particle_Emitter::onDraw(olc::PixelGameEngine* pge) { drawParticles(pge); }


/*#############################################################################
 * Asteroid_Particle
 *###########################################################################*/

olc::Sprite* Asteroid_Particle::sprite = nullptr;
olc::Decal*  Asteroid_Particle::decal = nullptr;
bool Asteroid_Particle::initDone = false;

void Asteroid_Particle::init(olc::PixelGameEngine* pge) {
    if(initDone) return;

    sprite = new olc::Sprite(2, 2);
    pge->SetDrawTarget(sprite);
        pge->FillRect(0, 0, 2, 2, pix_asteroid);
    pge->SetDrawTarget(nullptr);

    decal = new olc::Decal(sprite);

    initDone=true;
}
void Asteroid_Particle::deinit() {
    delete sprite;
    delete decal;
    initDone = false;
}


ParticleSystem::Particle* Asteroid_Particle::spawnNewParticle(){

    Asteroid_Particle* p = new Asteroid_Particle(this->em);

    p->pos.x = (RandF() * 8 - 4);
    p->pos.y = (RandF() * 8 - 4);
    p->directionFromPositionVector();
    p->lifetime = 2000;
    return (ParticleSystem::Particle*)p;

}

Asteroid_Particle::Asteroid_Particle() 
:Asteroid_Particle(nullptr)
{}

Asteroid_Particle::Asteroid_Particle(Asteroid_Particle_Emitter* em) 
{ this->em = em; }

bool Asteroid_Particle::onParticleUpdate(float deltaTime) {
    lifetime -= deltaTime * 1000.0;
    if(lifetime <= 0) return false;

    moveInDirection(6 * deltaTime);
    return true;
}

void Asteroid_Particle::onParticleDraw(olc::PixelGameEngine* pge){
    pge->DrawDecal(em->pos + pos, decal);  
};
