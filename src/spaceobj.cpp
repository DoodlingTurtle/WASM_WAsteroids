#include "spaceobj.h"
#include "config.h"

SpaceObj::SpaceObj() : SpaceObj::SpaceObj(1.0f){}
SpaceObj::SpaceObj( float radius ) {
    objRadius = radius;
    bIsAlive = false;
    renderer.defineWrappingArea(0, APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT, 0);
}

void SpaceObj::updatePosition(float deltaTime) {
    pos += velocity*deltaTime;
    renderer.updateDrawingInstances(&(this->pos), objRadius * scale);
}

void SpaceObj::getCollisionSphere(olc::vf2d *pos, float *radius) {
    if(pos != nullptr)
        *pos = this->pos;
    if(radius != nullptr)
        *radius = scale * objRadius;
}

void SpaceObj::draw(std::function<void(RGNDS::Transform*)> drawingLambda) {
    olc::vf2d posOrig = this->pos;

    for(olc::vf2d p : renderer.getInstances()) { 
        this->pos = p;
        drawingLambda(this);
    }

    this->pos = posOrig;
}

void SpaceObj::kill() {
    bIsAlive = false;
}

bool SpaceObj::isAlive() {
    return bIsAlive;
}
