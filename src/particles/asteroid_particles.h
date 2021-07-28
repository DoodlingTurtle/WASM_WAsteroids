#ifndef __Asteroid_Particles_H__
#define __Asteroid_Particles_H__

#include "../particles.h"
#include "../spaceobj.h"
#include "../transform.h"
#include "../olcPixelGameEngine.h"

class Asteroid_Particle_Emitter 
: public ParticleSystem::Emitter 
, public SpaceObj {
public:
    Asteroid_Particle_Emitter(int x, int y, float scale);

    void onParticleAssign(ParticleSystem::Particle*) override;
    void onNoParticlesLeft() override;

    std::vector<SpaceObj*>* onUpdate(float) override;  
    void onDraw(olc::PixelGameEngine*) override;

};

class Asteroid_Particle 
: public ParticleSystem::Particle
, protected RGNDS::Transform
{
public:
    Asteroid_Particle();
    Asteroid_Particle(Asteroid_Particle_Emitter*);

    Particle* spawnNewParticle(); 
    bool onParticleUpdate(float deltaTime);
    void onParticleDraw(olc::PixelGameEngine*);

    static void init(olc::PixelGameEngine*);
    static void deinit();
    
protected:
    Asteroid_Particle_Emitter* em;
    static olc::Sprite* sprite;
    static olc::Decal* decal;
    
    float lifetime;

private:
    static bool initDone;
};

#endif
