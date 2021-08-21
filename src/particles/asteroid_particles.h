#ifndef __Asteroid_Particles_H__
#define __Asteroid_Particles_H__

#include "./sprite_dissolve.h"
#include "gameobject.h"
#include "gamecomponent.h"
#include "spaceobj.h"
#include "gameobjects/asteroids.h"

class AsteroidExplosion 
: public SpriteDissolve
, public WorldDrawable
, public WorldUpdateable
, public GameObject
, public SpaceObj {
public:
    AsteroidExplosion(Asteroid*);

    void onEmitterFinished() override;

    void onUpdate(float deltaTime) override;
    void onDraw(olc::PixelGameEngine*) override;

} ;


#endif
