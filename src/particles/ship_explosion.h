#ifndef __Ship_Explosions_H__
#define __Ship_Explosions_H__

#include <vector>
#include "sprite_dissolve.h"
#include "../olcPixelGameEngine.h"
#include "../spaceobj.h"
#include "../gameobjects/ship.h"

class ShipExplosion
: public SpriteDissolve
, public SpaceObj
{
public:
    ShipExplosion(Ship* s);
    void onEmitterFinished() override;

    std::vector<SpaceObj*>* onUpdate(float deltaTime) override;
    void                    onDraw(olc::PixelGameEngine*) override;
};



#endif
