#pragma once
#include "olcPixelGameEngine.h"

class WorldDrawable {
    public:
        virtual void onDraw(olc::PixelGameEngine*) = 0;
};

class WorldUpdateable {
    public:
        virtual void onUpdate(float deltaTime) = 0;
};
