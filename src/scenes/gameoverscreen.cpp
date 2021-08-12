#include "./gameoverscreen.h"

#include <cstdio>
#include "../global.h"

void GameOverScreen::onStart() { 
    
    scoreStartLocation = { 117, 5 };
    scoreLocation = scoreStartLocation;
    scoreTargetLocation = {64.0f, 88.0f};

    playhead = 0.0f;
    playtime = 1.5f;

    //scoreAnimation.changeAnimatedObject(&scoreLocation);
    //scoreAnimation.moveTo(&scoreTargetLocation, 1500);

    //scoreAnimation.play();
}

void GameOverScreen::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {
    Global::asteroids->update(deltaTime);

    if(Global::gameInput->released&KEYPAD_START)
        exit();

    // Advance Playhead
    if(playhead < playtime) {
        playhead += deltaTime;
        if(playhead > playtime)
            playhead = playtime;

        scoreLocation = scoreStartLocation - (scoreStartLocation-scoreTargetLocation) * (playhead/playtime);
    }

     

    //scoreAnimation.update(deltaTime);

    //SpaceObj::MainGameUpdateData dat = { deltaTime };


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

    pge->DrawString({ 40, 296}, "Press Enter", olc::WHITE, 2);
}
