#include "./spaceobj.h"
#include "./config.h"
#include "./engine/Global.h"


SpaceObj::SpaceObj() : SpaceObj::SpaceObj(1.0f){}
SpaceObj::SpaceObj( float radius ) {
    objRadius = radius;
    renderer.defineWrappingArea(0, Global::layout->app_width, Global::layout->app_height, 0);

    moveVelocity = 0.0f;
    setRandomDirection();
}

float SpaceObj::getAngle() { return moveAngle; }
olc::vf2d SpaceObj::getDirection() { return moveDirection; }

void SpaceObj::pointTowardsPosition(const olc::vf2d& pos) {
    //olc::vf2d d = pos - this->pos;
    //float hyp = std::sqrt(d.x * d.x + d.y * d.y);
    // d.x /= hyp; d.y /= hyp;
    //setDirection(d)

    setDirection((pos - this->pos).norm());
    this->dir = this->moveDirection;
    this->ang = this->moveAngle;
}

void SpaceObj::setDirection(olc::vf2d dir) {
    if(dir.x < -1.0f || dir.x > 1.0f || dir.y < -1.0f || dir.y > 1.0f) 
        throw "SpaceObj::setDirection: is not a direction vector";

    moveDirection = dir;
    moveAngle = acos(dir.x);
}
void SpaceObj::setRandomDirection() { setAngle(RandF() * PI2); }
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

void SpaceObj::movePixelDistance(float px) {
    pos += (moveDirection * px);
    renderer.updateDrawingInstances(&(this->pos), objRadius * scale);
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

