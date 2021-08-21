#ifndef __Ship_Explosions_H__
#define __Ship_Explosions_H__

#include <vector>
#include "olcPixelGameEngine.h"
#include "gameobject.h"
#include "gamecomponent.h"
#include "spaceobj.h"

#include "gameobjects/ship.h"

#include "./sprite_dissolve.h"

class ShipExplosion
: public SpriteDissolve
, public GameObject
, public WorldUpdateable
, public WorldDrawable
, public SpaceObj
{
public:
    ShipExplosion(Ship* s);
    void onEmitterFinished() override;

    void onUpdate(float deltaTime) override;
    void onDraw(olc::PixelGameEngine*) override;
};

#endif
