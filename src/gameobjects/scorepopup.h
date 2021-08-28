#ifndef __ScorePopup_H__
#define __ScorePopup_H__

#include <vector>
#include <functional>

#include "../engine/olcPixelGameEngine.h"
#include "../engine/world/Object.h"
#include "../engine/world/components/Drawable.h"
#include "../engine/world/components/Updateable.h"

#include "../gamecomponents.h"
#include "../spaceobj.h"

using namespace RGNDS;

class ScorePopup 
: public GameObject
, public World::Drawable 
, public World::Updateable
, public SpaceObj {
public:
    ScorePopup(short score, float x, float y);

    void onUpdate(float deltaTime) override;
    void onDraw(olc::PixelGameEngine*) override;

protected:
    short score;        // Keeps track of what score is displayed
    short lifetime;      // for how many ticks this popup will stay 


};

#endif
