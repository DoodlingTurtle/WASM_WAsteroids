#ifndef __Asteroid_Particles_H__
#define __Asteroid_Particles_H__

#include "../particles.h"
#include "../spaceobj.h"
#include "../transform.h"
#include "../olcPixelGameEngine.h"

#include "spaceobj_emitter.h"

class Asteroid_Particle;

typedef SpaceObj_Emitter<Asteroid_Particle> Asteroid_Particle_Emitter;
typedef ParticleSystem<Asteroid_Particle_Emitter, Asteroid_Particle> t_AsteroidExplosion;

class AsteroidExplosion 
: public t_AsteroidExplosion 
, public SpaceObj {
public:
    AsteroidExplosion(int x, int y, float scale);

    std::vector<SpaceObj*>* onUpdate(float) override;  
    void onDraw(olc::PixelGameEngine*) override;
    bool allowDeleteAfterDeath() override; 
} ;

class Asteroid_Particle 
: public AsteroidExplosion::Particle
, protected RGNDS::Transform
{
public:
    Asteroid_Particle();
    Asteroid_Particle(Asteroid_Particle_Emitter*);

    Asteroid_Particle* spawnNewParticle(Asteroid_Particle_Emitter*); 
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
