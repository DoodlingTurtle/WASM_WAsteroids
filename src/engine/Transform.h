#pragma once

#include "./olcPixelGameEngine.h"

namespace RGNDS {

    class Transform {

    public:
        olc::vf2d pos;
        float scale = 1.0f;
        static Transform _default;
        

        Transform(float x=0, float y=0);
        virtual ~Transform();

        virtual void moveInDirection( float distance );

        olc::vf2d translate(olc::vf2d in, olc::vf2d* out = nullptr);
        

        void setAngle(float radiants);
        void setAngleRel( float radiants );

        void directionFromPositionVector();

        float ang = 0.0;
        olc::vf2d dir = {1.0f, 0.0f};

        olc::vf2d origin = { 0.0f, 0.0f };

    };

}
