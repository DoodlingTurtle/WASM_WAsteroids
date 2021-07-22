#ifndef __SPACEOBJ_H__
#define __SPACEOBJ_H__

#include <functional>
#include "olcPixelGameEngine.h"
#include "wraparoundrenderer.h"
#include "transform.h"

class SpaceObj : public RGNDS::Transform {
public:
    struct MainGameUpdateData {
        float deltaTime; 
        int keys_held; 
        int keys_up; 
        int keys_justpressed; 
    };

    struct MainGameDrawData {
        float deltaTime;
    };

    SpaceObj();
    SpaceObj(float objectRadius);

    olc::vd2d velocity;

    void updatePosition(float deltaTime);
    void getCollisionSphere(olc::vf2d *pos, float *radius);

    void draw(std::function<void(RGNDS::Transform*)> drawingLambda);

    virtual void onUpdate(MainGameUpdateData* ) {};
    virtual void onDraw(MainGameDrawData* ){};
    virtual short getScoreValue() { return 0; }

    virtual void kill();
    bool isAlive();

protected:
    WrapAroundRenderer renderer;
    float objRadius;
    bool bIsAlive;


};

#endif
