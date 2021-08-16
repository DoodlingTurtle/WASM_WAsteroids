#include "shot.h"
#include "../global.h"
#include "../collision.h"

Shots::Shot::Shot() : SpaceObj(3.0f)    
{
    scale=1;
    bIsAlive = false;
}

Shots::Shot::~Shot() {}

void Shots::Shot::revive(
        olc::vf2d* pos, 
        float ang,
        olc::Decal* spr
) {
    this->pos.x = pos->x;
    this->pos.y = pos->y;
    RGNDS::Transform::setAngle(ang);
    lifetime = 1000;
    moveInDirection(8.0);
    bIsAlive = true;
    decal = spr;
    updatePosition(0.0f);

    SpaceObj::setDirection(dir);
    SpaceObj::moveVelocity = 64.0f;
}

void Shots::Shot::onDraw(olc::PixelGameEngine* pge) {
    pge->SetDrawTarget(layer_shots);
    SpaceObj::draw([this](RGNDS::Transform *tr){
        Global::pge->DrawRotatedDecal(
                tr->pos, decal, 
                tr->ang, {tr->scale, tr->scale}
        );
    });
    pge->SetDrawTarget(nullptr); 
}

std::vector<SpaceObj*>* Shots::Shot::onUpdate(float deltaTime) {

    lifetime -= deltaTime * 250;    
    if(lifetime <= 0) {
        this->bIsAlive = false;
    }
    else {
        updatePosition(deltaTime);

        std::vector<Asteroids::Asteroid*> asteroids = Global::asteroids->getLiveAsteroids();
        RGNDS::Collision c;

        for(auto a : asteroids) {
            if(RGNDS::Collision::checkCircleOnCircle(
                ((RGNDS::Collision::Circle){
                    pos.x, pos.y, 2.0f
                }), a->getColliders(),
                &c
            )){
                a->markAsHit(&c);
                this->kill();
            }
        }

    }

    return nullptr;
}

/*#############################################################################
 * Shots
 *###########################################################################*/

Shots::Shots()
: sfx(nullptr)
{ 
    if(!sfx) sfx     = Mix_LoadWAV("./assets/sfx/sci-fi_sounds/laserSmall_002.ogg");
    sprShot = new olc::Sprite("./assets/sprites/shot.png"); 
    decShot = new olc::Decal(sprShot);
}

Shots::~Shots(){ 
    delete decShot;
    delete sprShot; 
    if(sfx)
        Mix_FreeChunk(sfx);
    sfx = nullptr;
}

Shots::Shot* Shots::spawnShot(float ang, olc::vf2d *pos) {

    for(int a = 0; a < MAX_SHOT_CNT; a++) {
        if(shots[a].isAlive()) continue;
        Mix_PlayChannel(-1, sfx, 0);
        Shot* shot = &shots[a];
        shot->revive(pos, ang, decShot);

        return shot;
    }

    return nullptr;
}

void Shots::killall() {
    Debug("Kill all shots");
    for(int a = 0; a < MAX_SHOT_CNT; a++)
        shots[a].kill();
}


