#ifndef WRAPAROUNDRENDERER_H
#define WRAPAROUNDRENDERER_H

#include <vector>
#include "olcPixelGameEngine.h"

class WrapAroundRenderer
{
    public:
        WrapAroundRenderer();
        virtual ~WrapAroundRenderer();

        void updateDrawingInstances(olc::vf2d* pos, float detectSphere);

        void defineWrappingArea(int top, int right, int bottom, int left);

        unsigned char getInstanceCnt();

        std::vector<olc::vf2d> getInstances();

    private:
        int top, right, bottom, left, width, height;

        std::vector<olc::vf2d> drawingInstances;

};

#endif // WRAPAROUNDRENDERER_H
