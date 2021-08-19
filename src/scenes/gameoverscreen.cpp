#include "./gameoverscreen.h"

#include <cstdio>
#include "global.h"
#include "assets.h"

void GameOverScreen::onStart() { 
    
    scoreStartLocation = { 117, 5 };
    scoreLocation = scoreStartLocation;
    scoreTargetLocation = {64.0f, 88.0f};

    playhead = 0.0f;
    playtime = 1.5f;

}

void GameOverScreen::onEnd() {
    Global::switchBGMusic(Assets::bgmMenu);
}

void GameOverScreen::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {
    Global::asteroids->update(deltaTime);

    if(Global::gameInput->released&KEYPAD_A)
        exit();

    // Advance Playhead
    if(playhead < playtime) {
        playhead += deltaTime;
        if(playhead > playtime)
            playhead = playtime;

        scoreLocation = scoreStartLocation - (scoreStartLocation-scoreTargetLocation) * (playhead/playtime);
    }

}
void GameOverScreen::onDraw(olc::PixelGameEngine* pge) {
    Global::asteroids->draw();

    char buffer[18];
    sprintf(buffer, "% 8d", Global::score);
    std::string s(buffer);

    pge->DrawString(scoreLocation, s, 
        olc::Pixel(32, 32, 196)
        , 2
    );

    pge->DrawString({ 40, 296}, "  Press P  ", olc::WHITE, 2);
    pge->DrawString({ 82, 312}, "to continue", olc::WHITE, 1);
}


