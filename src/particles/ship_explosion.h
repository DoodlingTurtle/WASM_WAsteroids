#ifndef __Ship_Explosions_H__
#define __Ship_Explosions_H__

#include <vector>
#include "../engine/olcPixelGameEngine.h"
#include "../engine/world/Object.h"
#include "../engine/world/components/Drawable.h"
#include "../engine/world/components/Updateable.h"

#include "../gamecomponents.h"

#include "../spaceobj.h"

#include "../gameobjects/ship.h"

#include "./sprite_dissolve.h"

using namespace RGNDS;

class ShipExplosion
: public SpriteDissolve
, public GameObject
, public World::Updateable
, public World::Drawable
, public SpaceObj
{
public:
    ShipExplosion(Ship* s);
    void onEmitterFinished() override;

    void onUpdate(float deltaTime) override;
    void onDraw(olc::PixelGameEngine*) override;
};

#endif
