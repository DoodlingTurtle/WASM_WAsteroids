#ifndef __Global_H__
#define __Global_H__

#include "config.h"
#include "olcPixelGameEngine.h"
#include "gameobjects/asteroids.h"
#include "particles.h"
#include "gameobjects/ship/shipstats.h"
#include "gameinput.h"
#include <SDL/SDL_mixer.h>

class Global {
public:
    static olc::PixelGameEngine* pge;
    static olc::Key gamecontrols[5];
    static Asteroids* asteroids;
    static ShipStats* shipStats;
    static GameInput* gameInput;
    static ScreenLayout* layout;
    static Mix_Music* bgMusic;

    static void switchBGMusic(const char* filename);

    static int score;

};

#endif
