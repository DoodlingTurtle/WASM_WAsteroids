#pragma once

#include "../engine/Transform.h"
#include "../engine/Lerp.h"
#include "../engine/Animation.h"
#include "../engine/Scene.h"

using namespace RGNDS;

class GameOverScreen : public Scene {
public:
    bool onUpdate(olc::PixelGameEngine*, float) override;
    void onDraw(olc::PixelGameEngine* pge) override;

    Scene* nextScene() override;

protected:
    void onEnd() override;
    void onStart() override;

private:
    olc::vf2d scoreLocation;
    RGNDS::Animation::Timeline timeline;
};
