#ifndef __Ship_Explosions_H__
#define __Ship_Explosions_H__

#include "../particles.h"
#include "../spaceobj.h"
#include "../transform.h"
#include "../olcPixelGameEngine.h"

#include "spaceobj_emitter.h"

class ShipExplosion_Particle;
class ShipExplosion_Emitter;

typedef SpaceObj_Emitter<ShipExplosion_Particle> t_ShipExplosion_Emitter;
typedef ParticleSystem<t_ShipExplosion_Emitter, ShipExplosion_Particle> t_ShipExplosion;

class ShipExplosion_Emitter 
: public t_ShipExplosion_Emitter {
    public:
        ShipExplosion_Emitter(int x, int y, SpaceObj* e, olc::vf2d vel, float speed );
        void onEmitterUpdate(float) override;

    protected:
        float velocity;
        float lifetime;
};

class ShipExplosion
: public SpaceObj
, public t_ShipExplosion {
public:
    ShipExplosion(int x, int y, olc::vf2d dir, float speed);
    void onDraw(olc::PixelGameEngine*) override;
    std::vector<SpaceObj*>* onUpdate(float) override;  
};


class ShipExplosion_Particle
: public t_ShipExplosion::Particle
, protected RGNDS::Transform
{
public:
    ShipExplosion_Particle();
    ShipExplosion_Particle(t_ShipExplosion_Emitter*);

    ShipExplosion_Particle* spawnNewParticle(t_ShipExplosion_Emitter*); 
    bool onParticleUpdate(float deltaTime);
    void onParticleDraw(olc::PixelGameEngine*);

    static void init(olc::PixelGameEngine*);
    static void deinit();
    
protected:
    t_ShipExplosion_Emitter* em;
    static olc::Sprite* sprite;
    static olc::Decal* decal;
    
    float lifetime;

private:
    static bool initDone;
};

#endif
