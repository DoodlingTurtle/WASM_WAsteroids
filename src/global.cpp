#include "global.h"
#include "config.h"

olc::PixelGameEngine* Global::pge = nullptr;
Asteroids* Global::asteroids = nullptr;
ParticleSystem* Global::particleSystem = nullptr;
int Global::score = 0;

olc::Key Global::gamecontrols[5] = {
    GameKeyMap[KEYPAD_UP],
    GameKeyMap[KEYPAD_LEFT],
    GameKeyMap[KEYPAD_RIGHT],
    GameKeyMap[KEYPAD_R],
    GameKeyMap[KEYPAD_A]
};

