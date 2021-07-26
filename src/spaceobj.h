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

    void updatePosition(float deltaTime);
    void getCollisionSphere(olc::vf2d *pos, float *radius);

    void draw(std::function<void(RGNDS::Transform*)> drawingLambda);

    //Adds On update can respond with nullptr or vector<SpaceObj*>
    virtual std::vector<SpaceObj*>* onUpdate(float deltaTime) { return nullptr; };
    
    virtual void onDraw(olc::PixelGameEngine* pge ){};
    virtual short getScoreValue() { return 0; }

    virtual void kill();
    virtual bool isAlive();

protected:
    olc::vd2d velocity;

    WrapAroundRenderer renderer;
    float objRadius;
    bool bIsAlive;


};

#endif
