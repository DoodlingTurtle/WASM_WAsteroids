#ifndef __Global_H__
#define __Global_H__

#include "olcPixelGameEngine.h"
#include "gameobjects/asteroids.h"
#include "particles.h"
#include "gameobjects/ship/shipstats.h"
#include "gameinput.h"

class Global {
public:
    static olc::PixelGameEngine* pge;
    static olc::Key gamecontrols[5];
    static Asteroids* asteroids;
    static ShipStats* shipStats;
    static GameInput* gameInput;

    static int score;

protected:

private:

};

#endif
