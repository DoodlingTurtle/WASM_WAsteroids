#pragma once

#include "../engine/olcPixelGameEngine.h"

#include "../engine/Scene.h"
#include "../gameobjects/asteroids.h"
#include "../gameobjects/ship.h"
#include "../particles/ship_explosion.h"

using namespace RGNDS;

class MainGameScreen : public Scene {

public:
    
    enum GAME_STATE {
        STATE_RUNNING,
        STATE_WON,
        STATE_LOST
    };

    MainGameScreen();
    void reset();

    bool onUpdate(olc::PixelGameEngine* pge, float dt) override;
    void onDraw(olc::PixelGameEngine* pge) override;
    
    float game_difficulty;        // difficulty goes from 1 to 16;

    GAME_STATE getState();

    Scene* nextScene() override;

#ifdef DEBUG_BUILD
    void endLevel();
#endif
    
protected:
    void onStart() override;
    void onEnd() override;

    GAME_STATE state;

private:
    RGNDS::Transform scorelocation;
    float scoreTimer;
};
