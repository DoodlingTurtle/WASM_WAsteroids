#include "./bullet.h"
#include "./asteroids.h"
#include "./scorepopup.h"
#include "../engine/global.h"
#include "../engine/assets.h"

#include <SDL/SDL_mixer.h>

Bullet::Bullet(float lifetime, const DecalRect sheetCoords, float radius)
    : SpaceObj(radius), GameObject({GameObject::BULLET})
, lifetime(lifetime), decalCoords(sheetCoords) , radius(radius)
{}

Bullet::~Bullet() {}

void Bullet::onUpdate(float deltaTime) {

    lifetime -= deltaTime * 0.25f;    
    if(lifetime <= 0) { assignAttribute(GameObject::DEAD); }

    else {
        updatePosition(deltaTime);

        auto list = Global::world->allBulletHitable();

        Physics::Collision c;
        
        for(auto a : list) {
            if(Physics::Collision::checkCircleOnCircle(
                (Physics::Collision::Circle{
                    pos.x, pos.y, radius 
                }), a->getColliders(),
                &c
            )){
                a->hitByBullet(this, &c);
                int score = a->getDestructionScore();

                for(auto m : modifiers)
                    score = m->updateScore(score, this);

                Global::score += score;
                Global::world->addGameObject(new ScorePopup(score, pos.x, pos.y));
                assignAttribute(GameObject::DEAD);
            }
        }
    }
}

void Bullet::onDraw(olc::PixelGameEngine *pge) {
    pge->SetDrawTarget(layer_shots);
    SpaceObj::draw([this](RGNDS::Transform *tr){
        Global::game->DrawPartialRotatedDecal(
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
    
    b->moveVelocity = velocity + 72.0f;
    b->pos = pos;
    b->setDirection(dir);

    return b;
}

