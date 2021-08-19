#include "./bullet.h"
#include "./asteroids.h"
#include "./scorepopup.h"
#include "global.h"

#include "assets.h"

#include <SDL/SDL_mixer.h>

Bullet::Bullet(float lifetime, const DecalRect sheetCoords, float radius)
:lifetime(lifetime), decalCoords(sheetCoords) , radius(radius)
{ this->bIsAlive = true; }

Bullet::~Bullet() {}

std::vector<SpaceObj*>* Bullet::onUpdate(float deltaTime) {

    std::vector<SpaceObj*>* spa = nullptr;

    lifetime -= deltaTime * 0.25f;    
    if(lifetime <= 0) { this->kill(); }

    else {
        updatePosition(deltaTime);

        std::vector<Asteroids::Asteroid*> asteroids = Global::asteroids->getLiveAsteroids();
        RGNDS::Collision c;

        for(auto a : asteroids) {
            if(RGNDS::Collision::checkCircleOnCircle(
                ((RGNDS::Collision::Circle){
                    pos.x, pos.y, radius 
                }), a->getColliders(),
                &c
            )){
                spa = new std::vector<SpaceObj*>();

                a->markAsHit(&c);
                int score = 100/a->scale;

                for(auto m : modifiers)
                    score = m->updateScore(score, this, spa);

                Global::score += score;
                spa->push_back(new ScorePopup(score, a->pos.x, a->pos.y));
                this->kill();
            }
        }
    }

    return spa;

}

void Bullet::onDraw(olc::PixelGameEngine *pge) {
    pge->SetDrawTarget(layer_shots);
    SpaceObj::draw([this](RGNDS::Transform *tr){
        Global::pge->DrawPartialRotatedDecal(
                tr->pos, Assets::bullets->Decal(), tr->ang, 
                decalCoords.coords + decalCoords.size / 2.0f,
                decalCoords.coords, decalCoords.size,
                {tr->scale, tr->scale}
        );
    });
    pge->SetDrawTarget(nullptr); 
}

Bullet* Bullet::clone(olc::vf2d pos, olc::vf2d dir, float velocity) {
    Bullet* b = new Bullet(lifetime, decalCoords, radius);
    
    b->moveVelocity = 72.0f;
    b->pos = pos;
    b->setDirection(dir);

    return b;
}

bool Bullet::allowDeleteAfterDeath() { return true; }
