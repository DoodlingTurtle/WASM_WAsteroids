#include "./bullet.h"
#include "./asteroids.h"
#include "./scorepopup.h"
#include "../engine/Global.h"
#include "../engine/Assets.h"

#include <SDL/SDL_mixer.h>

Bullet::Bullet(float lifetime, const DecalRect sheetCoords, float radius)
    : SpaceObj(radius), GameObject({ GameObject::BULLET })
    , lifetime(lifetime), totalLifetime(lifetime), decalCoords(sheetCoords), radius(radius)
    , isClone(false)
{}

Bullet::~Bullet() {
    if (!isClone) {
        for (auto m : modifiers)
            delete m;
    }
    
    modifiers.clear();
}

void Bullet::onUpdate(float deltaTime) {

    lifetime -= deltaTime * 0.25f;    
    if(lifetime <= 0) { assignAttribute(GameObject::DEAD); }
    else {
        updatePosition(deltaTime);

        auto list = this->getHitables(); // Global::world->allBulletHitable();

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

    Bullet* b = this->newInstance();
    b->lifetime = this->lifetime;
    b->radius = this->radius;
    b->decalCoords = this->decalCoords;
    
    b->moveVelocity = velocity + 72.0f;
    b->pos = pos;
    b->setDirection(dir);
    b->modifiers = modifiers;

    b->isClone = true;

    return b;
}

float Bullet::getLifetime() { return lifetime/totalLifetime; }

void Bullet::addModifier(BulletModifier* m) { 
    modifiers.push_back(m); }
