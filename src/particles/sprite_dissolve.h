#pragma once

#include "../engine/olcPixelGameEngine.h"
#include "../engine/Transform.h"
#include "../particles.h"

using namespace RGNDS;

class SpriteDissolve_Emitter;
class SpriteDissolve_Particle;

typedef ParticleSystem<SpriteDissolve_Emitter, SpriteDissolve_Particle> t_SpriteDissolve;

/*#############################################################################
 * SpriteDissovlve
 *###########################################################################*/
class SpriteDissolve 
: public t_SpriteDissolve
{
public:
    SpriteDissolve(olc::Sprite* spr, Transform* tr,
            float maxParticleDistance = 10.0f, /* Defines how far each particle can move from its origin during its lifetime */
            float maxParticleLifetimeSecs = 1.0f /* defines how many seconds a particle can stay active at maximum*/
    );
    virtual void onEmitterFinished() {}

    void onUpdate(float deltaTime);
    void onDraw(olc::PixelGameEngine*);
};

/*#############################################################################
 * SpriteDissolve_Emitter
 *###########################################################################*/
class SpriteDissolve_Emitter 
: public t_SpriteDissolve::Emitter
, public Transform
{
public:
    SpriteDissolve_Emitter(
            olc::Sprite*, 
            Transform*, 
            SpriteDissolve*,
            float maxParticleDistance = 10.0f, /* Defines how far each particle can move from its origin during its lifetime */
            float maxParticleLifetimeSecs = 1.0f /* defines how many seconds a particle can stay active at maximum*/
    );
    ~SpriteDissolve_Emitter();
    void onNoParticlesLeft();


private:
    olc::Decal* decal;
    SpriteDissolve* system;

    friend class SpriteDissolve_Particle;

};

/*#############################################################################
 * SpriteDissolve_Particle
 *###########################################################################*/
class SpriteDissolve_Particle 
: public t_SpriteDissolve::Particle
, public Transform
{
public:
    /** \brief consturctor
     * \param startCoords  - defines, where on the screen, the particle will start
     * \param pxx - the x coord of the pixel on the decal
     * \param pxy - the y coord of the pixel on the decal
     * \param em  - the SpriteDissolve_Emitter, that spawned this particle
     * \param speed - how fast the particle moves away from its origin
     * \param maxLifetime - how many seconds the particle will exist at full opacity
     */
    SpriteDissolve_Particle(
            olc::vf2d startCoords, olc::vf2d emitterPosition, 
            olc::Pixel, 
            float speed=10.0f, float maxLifetime=1.0f);

    SpriteDissolve_Particle* spawnNewParticle(SpriteDissolve_Emitter* e);
    bool onParticleUpdate(float deltaTime);
    void onParticleDraw(olc::PixelGameEngine*);

protected:
    float lifetime;
    olc::vf2d px;
    float speed;
    float maxLifetime;
    olc::Pixel pixel;
};
