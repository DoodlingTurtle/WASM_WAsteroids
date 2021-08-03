#ifndef MAINGAMESCREEN_H
#define MAINGAMESCREEN_H

#include "../olcPixelGameEngine.h"
#include "../scene.h"
#include "../gameobjects/asteroids.h"
#include "../gameobjects/ship.h"
#include "../particles/ship_explosion.h"

class MainGameScreen : public Scene {

public:
    
    enum GAME_STATE {
        STATE_RUNNING,
        STATE_WON,
        STATE_LOST
    };

    MainGameScreen();
    void reset();

    void onUpdate(olc::PixelGameEngine* pge, float dt) override;
    void onDraw(olc::PixelGameEngine* pge) override;
    
    float game_difficulty;        // difficulty goes from 1 to 16;

    GAME_STATE getState();

protected:
    void onStart() override;
    void onEnd() override;

    GAME_STATE state;

private:
    RGNDS::Transform scorelocation;
    float scoreTimer;

    Ship* ship;

    bool shipSurvived;
    ShipExplosion* shipexp; 
};

#endif
