#include "global.h"
#include "config.h"

olc::PixelGameEngine* Global::pge = nullptr;
Asteroids* Global::asteroids = nullptr;
ShipStats* Global::shipStats = nullptr;
GameInput* Global::gameInput = nullptr;
ScreenLayout* Global::layout = nullptr;
Mix_Music* Global::bgMusic   = nullptr;

int Global::score = 0;

void Global::switchBGMusic(const char* filename) {
    if(bgMusic) {
        Mix_HaltMusic();
        Mix_FreeMusic(bgMusic);
        bgMusic = nullptr;
    }

    if(filename != nullptr) {
        bgMusic = Mix_LoadMUS(filename);
        if(bgMusic) Mix_PlayMusic(bgMusic, -1);
    }
}

olc::Key Global::gamecontrols[5] = {
    GameKeyMap[KEYPAD_UP],
    GameKeyMap[KEYPAD_LEFT],
    GameKeyMap[KEYPAD_RIGHT],
    GameKeyMap[KEYPAD_R],
    GameKeyMap[KEYPAD_A]
};

