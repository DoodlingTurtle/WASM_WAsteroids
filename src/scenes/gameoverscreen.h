#ifndef __GameOverScreen_H__
#define __GameOverScreen_H__

#include "scene.h"
#include "transform.h"
#include "lerp.h"

//#include "animation.h"

class GameOverScreen : public Scene {
public:
    void onUpdate(olc::PixelGameEngine*, float) override;
    void onDraw(olc::PixelGameEngine* pge) override;

protected:
    void onEnd() override;
    void onStart() override;

private:
    RGNDS::Lerp<olc::vf2d> lerp;
    olc::vf2d scoreLocation;

};

#endif
