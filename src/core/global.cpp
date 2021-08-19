#include "global.h"
#include "config.h"

#undef REGISTER_GLOBAL
#define REGISTER_GLOBAL(t, e, v) t Global::e = v;
#include "global.hpp"

void Global::switchBGMusic(Mix_Music* asset) {
    Mix_HaltMusic();
    if(asset) Mix_PlayMusic(asset, -1);
}

olc::Key Global::gamecontrols[5] = {
    GameKeyMap[KEYPAD_UP],
    GameKeyMap[KEYPAD_LEFT],
    GameKeyMap[KEYPAD_RIGHT],
    GameKeyMap[KEYPAD_R],
    GameKeyMap[KEYPAD_A]
};

