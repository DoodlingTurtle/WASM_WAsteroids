#ifndef __GameOverScreen_H__
#define __GameOverScreen_H__

#include "scene.h"
#include "transform.h"

//#include "animation.h"

class GameOverScreen : public Scene {
public:
    void onUpdate(olc::PixelGameEngine*, float) override;
    void onDraw(olc::PixelGameEngine* pge) override;

protected:
    void onEnd() override;
    void onStart() override;

private:
    olc::vf2d scoreStartLocation;
    olc::vf2d scoreLocation;
    olc::vf2d scoreTargetLocation;

    float playhead;
    float playtime;
    //Animation scoreAnimation;
};

#endif
