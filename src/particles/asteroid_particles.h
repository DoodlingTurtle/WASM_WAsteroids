#ifndef __Asteroid_Particles_H__
#define __Asteroid_Particles_H__

#include "sprite_dissolve.h"
#include "../gameobjects/asteroids.h"
#include "../spaceobj.h"

class AsteroidExplosion 
: public SpriteDissolve
, public SpaceObj {
public:
    AsteroidExplosion(Asteroids::Asteroid*);

    void onEmitterFinished() override;

    std::vector<SpaceObj*>* onUpdate(float deltaTime) override;
    void                    onDraw(olc::PixelGameEngine*) override;

    bool allowDeleteAfterDeath() override; 
} ;


#endif
