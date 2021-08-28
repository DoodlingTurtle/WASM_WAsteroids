#pragma once

#include "./sprite_dissolve.h"
#include "../engine/world/Object.h"
#include "../engine/world/components/Updateable.h"
#include "../engine/world/components/Drawable.h"
#include "../gamecomponents.h"
#include "../spaceobj.h"
#include "../gameobjects/asteroids.h"

using namespace RGNDS;

class AsteroidExplosion 
: public SpriteDissolve
, public World::Updateable
, public World::Drawable
, public GameObject
, public SpaceObj {
public:
    AsteroidExplosion(Asteroid*);

    void onEmitterFinished() override;

    void onUpdate(float deltaTime) override;
    void onDraw(olc::PixelGameEngine*) override;

} ;
