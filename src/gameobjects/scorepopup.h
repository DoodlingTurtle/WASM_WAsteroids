#ifndef __ScorePopup_H__
#define __ScorePopup_H__

#include <vector>
#include <functional>

#include "olcPixelGameEngine.h"
#include "gameobject.h"
#include "spaceobj.h"

class ScorePopup : public GameObject, public SpaceObj {
public:
    ScorePopup(short score, float x, float y);

    std::vector<SpaceObj*>* onUpdate(float deltaTime) override;
    void onDraw(olc::PixelGameEngine*) override;

protected:
    short score;        // Keeps track of what score is displayed
    short lifetime;      // for how many ticks this popup will stay 


};

#endif
