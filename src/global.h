#ifndef __Global_H__
#define __Global_H__

#include "olcPixelGameEngine.h"
#include "gameobjects/asteroids.h"
#include "particles.h"
#include "gameobjects/ship/shipstats.h"

class Global {
public:
    static olc::PixelGameEngine* pge;
    static olc::Key gamecontrols[5];
    static Asteroids* asteroids;
    static ParticleSystem* particleSystem;
    static ShipStats* shipStats;

    static int score;

protected:

private:

};

#endif
