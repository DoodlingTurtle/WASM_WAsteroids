#include "spaceobj.h"
#include "config.h"

SpaceObj::SpaceObj() : SpaceObj::SpaceObj(1.0f){}
SpaceObj::SpaceObj( float radius ) {
    objRadius = radius;
    bIsAlive = false;

    renderer.defineWrappingArea(0, APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT, 0);

    moveVelocity = 0.0f;
    setRandomDirection();
}

float SpaceObj::getAngle() { return moveAngle; }
olc::vf2d SpaceObj::getDirection() { return moveDirection; }

void SpaceObj::setDirection(olc::vf2d dir) {
    if(dir.x < -1.0f || dir.x > 1.0f || dir.y < -1.0f || dir.y > 1.0f) 
        throw "SpaceObj::setDirection: is not a direction vector";

    moveDirection = dir;
    moveAngle = acos(dir.x);
}
void SpaceObj::setRandomDirection() { setAngle(RandF()); }
void SpaceObj::setAngle(float radiants) {
    moveAngle = radiants;
    moveDirection = olc::vf2d(cos(moveAngle), sin(moveAngle));
}
void SpaceObj::getCollisionSphere(olc::vf2d *pos, float *radius) {
    if(pos != nullptr)
        *pos = this->pos;
    if(radius != nullptr)
        *radius = scale * objRadius;
}

void SpaceObj::updatePosition(float deltaTime) {
    pos += (moveDirection * moveVelocity) * deltaTime;

    renderer.updateDrawingInstances(&(this->pos), objRadius * scale);
}

void SpaceObj::draw(std::function<void(RGNDS::Transform*)> drawingLambda) {
    olc::vf2d posOrig = this->pos;

    for(olc::vf2d p : renderer.getInstances()) { 
        this->pos = p;
        drawingLambda(this);
    }

    this->pos = posOrig;
}

void SpaceObj::kill() { bIsAlive = false; }

bool SpaceObj::isAlive() { return bIsAlive; }
