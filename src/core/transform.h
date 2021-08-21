#ifndef __RGNDS_TRANSFORM_H__
#define __RGNDS_TRANSFORM_H__ 1

#include "olcPixelGameEngine.h"

namespace RGNDS {

    class Transform {

    public:
        olc::vf2d pos;
        float scale = 1.0f;
        static Transform _default;
        

        Transform(float x=0, float y=0);
        virtual ~Transform();

        virtual void moveInDirection( float distance );

        void translate(olc::vf2d* in, olc::vf2d* out);

        void setAngle(float radiants);
        void setAngleRel( float radiants );

        void directionFromPositionVector();

        float ang = 0.0;
        olc::vf2d dir = {1.0f, 0.0f};

    };

}

#endif // __RGNDS_TRANSFORM_H__
