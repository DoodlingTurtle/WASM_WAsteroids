#ifndef WRAPAROUNDRENDERER_H
#define WRAPAROUNDRENDERER_H

#include "olcPixelGameEngine.h"

class WrapAroundRenderer
{
    public:
        WrapAroundRenderer();
        virtual ~WrapAroundRenderer();

        void updateDrawingInstances(olc::vf2d* pos, float detectSphere);

        void defineWrappingArea(int top, int right, int bottom, int left);

        unsigned char getInstanceCnt();
        olc::vf2d getInstance(unsigned char index);

    private:
        int top, right, bottom, left, width, height;

        olc::vf2d drawingInstances[4];
        unsigned char drawingInstanceCnt = 1;
};

#endif // WRAPAROUNDRENDERER_H
