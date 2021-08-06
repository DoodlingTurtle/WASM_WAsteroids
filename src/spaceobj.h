#ifndef __SPACEOBJ_H__
#define __SPACEOBJ_H__

#include <functional>
#include "olcPixelGameEngine.h"
#include "wraparoundrenderer.h"
#include "transform.h"

class SpaceObj : public RGNDS::Transform {
public:

    SpaceObj();
    SpaceObj(float objectRadius);

    float moveVelocity;

    // Setters 
    void setAngle(float radiants);
    void setDirection(olc::vf2d directionVector);
    void setRandomDirection();

    void updatePosition(float deltaTime);
    void movePixelDistance(float px);

    // Getters
    float getAngle();
    olc::vf2d getDirection();
    void getCollisionSphere(olc::vf2d *pos, float *radius);
    void draw(std::function<void(RGNDS::Transform*)> drawingLambda);

    // Virtual functionn
    virtual std::vector<SpaceObj*>* onUpdate(float deltaTime) { return nullptr; };
    virtual bool allowDeleteAfterDeath() { return false; }
    virtual void onDraw(olc::PixelGameEngine* pge ){};
    virtual void kill();
    virtual bool isAlive();


protected:
    WrapAroundRenderer renderer;
    float objRadius;
    bool bIsAlive;

private:
    float moveAngle;
    olc::vf2d moveDirection;

};

#endif
