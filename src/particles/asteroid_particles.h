#ifndef __Asteroid_Particles_H__
#define __Asteroid_Particles_H__

#include "./sprite_dissolve.h"
#include "gameobject.h"
#include "spaceobj.h"
#include "gameobjects/asteroids.h"

class AsteroidExplosion 
: public SpriteDissolve
, public GameObject
, public SpaceObj {
public:
    AsteroidExplosion(Asteroid*);

    void onEmitterFinished() override;

    std::vector<SpaceObj*>* onUpdate(float deltaTime) override;
    void                    onDraw(olc::PixelGameEngine*) override;

} ;


#endif
