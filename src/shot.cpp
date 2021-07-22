#include "./shot.h"
//#include "gamestatemaingame.h"

Shot _instances[MAX_SHOT_CNT];
std::vector<SpaceObj*>* Shot::shotGameObjects = nullptr;

void Shot::cleanup() {
    for(int a = 0; a < MAX_SHOT_CNT; a++)
        _instances[a].kill();
}

void Shot::Spawn(float ang, olc::vf2d *pos) {
    if(shotGameObjects == nullptr) return;

    for(int a = 0; a < MAX_SHOT_CNT; a++) {
        if(_instances[a].bIsAlive) continue;

        Shot* shot = &_instances[a];
        shot->pos.x = pos->x;
        shot->pos.y = pos->y;
        shot->setAngle(ang);
        shot->lifetime = 1000;
        shot->moveInDirection(8.0);
        shot->bIsAlive = true;
        shotGameObjects->push_back(shot);
        return;
    }
}

Shot::Shot() : SpaceObj(3.0f)    
{
    scale=1;
    bIsAlive = false;
    velocity.x = 0;
    velocity.y = 0;
}

Shot::~Shot() {}

void Shot::onDraw(SpaceObj::MainGameDrawData* d) {
    SpaceObj::draw([this](RGNDS::Transform *tr){
		    //TODO: implement new draw routine
        //RGNDS::GL2D::PolyShape::draw(Engine_Color16(1, 31, 31, 31), tr, 21 * ((float)lifetime/1000.0f) + 10);
    });
}

void Shot::onUpdate(SpaceObj::MainGameUpdateData* dat) {

    float deltaTime =dat->deltaTime;

    lifetime -= deltaTime * 250;        // 1000 / 4 = 4 Seconds of lifetime
    if(lifetime <= 0) {
        this->bIsAlive = false;
    }
    else {
        moveInDirection(64.0f * deltaTime);
        updatePosition(deltaTime);
    }
}

std::vector<Shot*> Shot::getShots() {
    std::vector<Shot*> out;

    for(int a = 0; a < MAX_SHOT_CNT; a++) 
        if(_instances[a].isAlive())
            out.push_back(&_instances[a]);

    return out;
}
