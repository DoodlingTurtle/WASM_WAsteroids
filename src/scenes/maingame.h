#ifndef MAINGAMESCREEN_H
#define MAINGAMESCREEN_H

#include "../olcPixelGameEngine.h"
#include "../scene.h"
#include "../gameobjects/asteroids.h"
#include "../gameobjects/ship.h"

class MainGameScreen : public Scene {

public:
    MainGameScreen(Asteroids*, int* score);

    void onUpdate(olc::PixelGameEngine* pge, float dt) override;
    void onDraw(olc::PixelGameEngine* pge) override;

    bool wasGameWon();
    
    float game_difficulty;        // difficulty goes from 1 to 16;
    
protected:
    void onStart() override;
    void onEnd() override;

private:
    RGNDS::Transform scorelocation;
    float scoreTimer;

    Asteroids* asteroids;
    int* score;

    Ship* ship;
};

#endif
