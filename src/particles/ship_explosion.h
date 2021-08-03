#ifndef __Ship_Explosions_H__
#define __Ship_Explosions_H__

#include "../particles.h"
#include "../spaceobj.h"
#include "../transform.h"
#include "../olcPixelGameEngine.h"

#include "spaceobj_emitter.h"

class ShipExplosion_Particle;
typedef SpaceObj_Emitter<ShipExplosion_Particle> ShipExplosion_Emitter;
typedef ParticleSystem<ShipExplosion_Emitter, ShipExplosion_Particle> t_ShipExplosion;


class ShipExplosion
: public SpaceObj
, public t_ShipExplosion {
public:
    ShipExplosion(int x, int y);
    void onDraw(olc::PixelGameEngine*) override;
    std::vector<SpaceObj*>* onUpdate(float) override;  
};


class ShipExplosion_Particle
: public t_ShipExplosion::Particle
, protected RGNDS::Transform
{
public:
    ShipExplosion_Particle();
    ShipExplosion_Particle(ShipExplosion_Emitter*);
    virtual ~ShipExplosion_Particle();

    ShipExplosion_Particle* spawnNewParticle(ShipExplosion_Emitter*); 
    bool onParticleUpdate(float deltaTime);
    void onParticleDraw(olc::PixelGameEngine*);

    static void init(olc::PixelGameEngine*);
    static void deinit();
    
protected:
    ShipExplosion_Emitter* em;
    static olc::Sprite* sprite;
    static olc::Decal* decal;
    
    float lifetime;

private:
    static bool initDone;
};

#endif
