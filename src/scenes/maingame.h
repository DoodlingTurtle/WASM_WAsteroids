#pragma once

#include "../engine/olcPixelGameEngine.h"

#include "../engine/Scene.h"
#include "../gameobjects/asteroids.h"
#include "../gameobjects/ship.h"
#include "../particles/ship_explosion.h"

#define BGM_TRACKS 5

using namespace RGNDS;

class MainGameScreen : public Scene {

public:
    enum class GAME_STATE {
        STATE_RUNNING,
        STATE_WON,
        STATE_LOST
    };

    MainGameScreen();

    bool onUpdate(olc::PixelGameEngine* pge, float dt) override;
    void onDraw(olc::PixelGameEngine* pge) override;
    
    float game_difficulty;        // difficulty goes from 1 to 16;

    Scene* nextScene() override;

    void updateBGM();

protected:
    void onStart(olc::PixelGameEngine*) override;
    void onEnd() override;

    GAME_STATE state;

private:
    RGNDS::Transform scorelocation;
    float scoreTimer;

    static Mix_Music** bgMusic[BGM_TRACKS];
};
