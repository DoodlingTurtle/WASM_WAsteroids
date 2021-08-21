#include "./bullet.h"
#include "./asteroids.h"
#include "./scorepopup.h"
#include "global.h"

#include "assets.h"

#include <SDL/SDL_mixer.h>

Bullet::Bullet(float lifetime, const DecalRect sheetCoords, float radius)
: SpaceObj(radius)
, lifetime(lifetime), decalCoords(sheetCoords) , radius(radius)
{}

Bullet::~Bullet() {}

void Bullet::onUpdate(float deltaTime) {

    lifetime -= deltaTime * 0.25f;    
    if(lifetime <= 0) { assignAttribute(GameObject::DEAD); }

    else {
        updatePosition(deltaTime);

        //TODO: Replace with GameObject::BULLET_COLLIDEABLE
        auto asteroids = Global::world->findByAttribute(GameObject::ASTEROID);

        RGNDS::Collision c;
        Asteroid* ast;
        for(auto a : asteroids) {
            ast = (Asteroid*)a;

            if(RGNDS::Collision::checkCircleOnCircle(
                (RGNDS::Collision::Circle{
                    pos.x, pos.y, radius 
                }), ast->getColliders(),
                &c
            )){
                ast->markAsHit(&c);
                int score = 100/ast->scale;

                for(auto m : modifiers)
                    score = m->updateScore(score, this);

                Global::score += score;
                Global::world->addGameObject(new ScorePopup(score, ast->pos.x, ast->pos.y));
                assignAttribute(GameObject::DEAD);
            }
        }
    }
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

