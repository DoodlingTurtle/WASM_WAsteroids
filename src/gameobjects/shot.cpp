#include "shot.h"
#include "../olcPGEX_Graphics2D.h"

Shots::Shot::Shot() : SpaceObj(3.0f)    
{
    scale=1;
    bIsAlive = false;
    velocity.x = 0;
    velocity.y = 0;
}

Shots::Shot::~Shot() {}

void Shots::Shot::revive(
        olc::vf2d* pos, 
        float ang,
        olc::Sprite* spr
) {
    this->pos.x = pos->x;
    this->pos.y = pos->y;
    setAngle(ang);
    lifetime = 1000;
    moveInDirection(8.0);
    bIsAlive = true;
    sprite = spr;
}

void Shots::Shot::onDraw(olc::PixelGameEngine* pge) {
    SpaceObj::draw([this](RGNDS::Transform *tr){
        olc::GFX2D::Transform2D tra;
        tr->toTransform2D(3, 3, &tra); 
        olc::GFX2D::DrawSprite(sprite, tra);
    });
}

std::vector<SpaceObj*>* Shots::Shot::onUpdate(float deltaTime) {

    lifetime -= deltaTime * 250;        // 1000 / 4 = 4 Seconds of lifetime    
    if(lifetime <= 0) {
        this->bIsAlive = false;
    }
    else {
        moveInDirection(64.0f * deltaTime);
        updatePosition(deltaTime);
    }

    return nullptr;
}

/*#############################################################################
 * Shots
 *###########################################################################*/

Shots::Shots() { sprShot = new olc::Sprite("./assets/shot.png"); }
Shots::~Shots(){ delete sprShot; }

Shots::Shot* Shots::spawnShot(float ang, olc::vf2d *pos) {

    for(int a = 0; a < MAX_SHOT_CNT; a++) {
        if(shots[a].isAlive()) continue;

        Shot* shot = &shots[a];
        shot->revive(pos, ang, sprShot);

        return shot;
    }

    return nullptr;
}

void Shots::killall() {
    for(int a = 0; a < MAX_SHOT_CNT; a++)
        shots[a].kill();
}

