#ifndef __RGNDS_TRANSFORM_CPP__
#define __RGNDS_TRANSFORM_CPP__

#include "config.h"
#include "./transform.h"
#include <math.h>

namespace RGNDS {
    Transform Transform::_default = Transform();

    Transform::Transform(float x, float y){
        pos.x = x;
        pos.y = y;
    }
    Transform::~Transform(){}

    void Transform::setAngleRel( float radiants ) {
        setAngle(ang + radiants);
    }
    void Transform::setAngle( float radiants ) {
        if(radiants < 0) {
            radiants = PI2 + radiants;
        }

        if(radiants > PI2) {
            radiants -= PI2;
        }

        ang = radiants;
        dir.y = sin(ang);
        dir.x = cos(ang);
    }

    void Transform::moveInDirection( float distance ) {
        pos += dir * distance;
    }

    void Transform::directionFromPositionVector() {
        float dist = sqrt(pos.x * pos.x + pos.y * pos.y);
        dir.x = pos.x / dist;
        dir.y = pos.y / dist;
    }

    void Transform::translate(olc::vf2d* in, olc::vf2d* out) {
        
        /*
        +-  -+   +--                  --+   +-  -+
        |out.x| = | cos(ang), - sin(ang) | * |in.x|
        |out.y|   | sin(ang),   cos(ang) |   |in.y|
        +-  -+   +--                  --+   +-  -+
        */
        out->x = dir.x * in->x + -dir.y * in->y;
        out->y = dir.y * in->x + dir.x * in->y; 

        *out *= scale;
        *out += pos;
    }

}
#endif // __RGNDS_TRANSFORM_CPP__
