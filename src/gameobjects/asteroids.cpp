#include "./asteroids.h"
#include "config.h"
#include "global.h"
#include "assets.h"

#include "particles/asteroid_particles.h"

#include "./scorepopup.h"

#include <stdio.h>
using namespace std;

Asteroid::Asteroid() 
: GameObject({
    GameObject::ASTEROID,
    GameObject::SPACE_OBJ_DRAW,
    GameObject::SPACE_OBJ_UPDATE,
    GameObject::SHIP_KILLER,
    GameObject::BULLET_COLLIDEABLE
})
, SpaceObj(32.0f)
, sprite(nullptr), decal(nullptr), killOnNextUpdate(false)
{}

void Asteroid::markAsHit( const RGNDS::Collision* c) { 
    setDirection(c->overlapDir ); 
    killOnNextUpdate = true;
}

float _getradius() {
    return 22 + rand()%10;
}

void Asteroid::generateShape() {
    olc::PixelGameEngine* pge = Global::pge;

    if(sprite == nullptr)
        sprite = new olc::Sprite(64, 64);

	pge->SetDrawTarget(sprite);

        pge->Clear(olc::BLANK);

        float angle = 0.0f;
        float lastsegment = 7.0f;
        float segment = PI2 / (lastsegment+1.0f);
        float radius = _getradius();
        
        float x = 0.0f, y = 0.0f;
        float x1 = sin(angle)*radius;
        float y1 = cos(angle)*radius;
        float startx = x1;
        float starty = y1;

        for(float a = 0; a <= lastsegment; a++) {
            x = x1;
            y = y1;
            angle += segment;
            radius = _getradius();
            if(a == lastsegment) {
                x1 = startx;
                y1 = starty;
            }
            else {
                x1 = sin(angle)*radius;
                y1 = cos(angle)*radius;
            }
            
            pge->FillTriangle(
                    32, 32, 
                    32 + x, 32 + y, 
                    32 + x1, 32 + y1, 
                    pix_asteroid
            );
        }

	pge->SetDrawTarget(nullptr);

    if(decal != nullptr)
        delete decal;

    decal = new olc::Decal(sprite);
}


void Asteroid::bringBackToLife(
        olc::vf2d pos, bool generateNewShape, 
        SIZES size,
        olc::vf2d direction, float velocity
) {
    Debug("revive Asteroid " << this);

    if(direction.x == 0 && direction.y == 0) 
        setRandomDirection();
    else 
        setDirection(direction);

    if(velocity < 0.00) moveVelocity = (float)(rand()%21 + 9);
    else                moveVelocity = velocity;

    spinSpeed = (RandF() * 0.5 + 0.5) * 0.0625; // Spin by 360� every 16 Seconds (at max spinspeed)

    this->pos.x = pos.x;
	this->pos.y = pos.y;

    this->size = size;
    if(size == Asteroid::SIZE_RANDOM) 
        size = static_cast<SIZES>(rand()%3);

    switch(size) {
        case Asteroid::SIZE_SMALL: {
            this->scale = 0.25f; break; }
                                    
        case Asteroid::SIZE_MIDDLE: {
            this->scale = 0.5f; break; }

        case Asteroid::SIZE_LARGE: 
        default: {
            this->scale = 1.0f; break; }
    }

    if(generateNewShape)
        generateShape();

    killOnNextUpdate = false;

    updatePosition(0.0f);

}

std::vector<SpaceObj*>* Asteroid::onUpdate(float deltatime) {

    if(killOnNextUpdate) {

        std::vector<SpaceObj*>* spa;

        playSFX();
        if(this->size != Asteroid::SIZE_SMALL) {

            SIZES size = static_cast<SIZES>( static_cast<int>(this->size)-1);

            olc::vf2d moveDirection = getDirection();

            Asteroid* ast = new Asteroid(); 
            ast->bringBackToLife(
                    pos, true, size, 
                    {-moveDirection.y, moveDirection.x},
                    moveVelocity
            );
            ast->movePixelDistance(28.0f * scale);
            Global::world->addGameObject(ast); 
            
            ast->bringBackToLife(
                    pos, true, size, 
                    {moveDirection.y, -moveDirection.x}, 
                    moveVelocity
            );
            ast->movePixelDistance(28.0f * scale);
            Global::world->addGameObject(ast); 
        }

        //Spawn AsteroidExplosion at go->pos
        AsteroidExplosion* e = new AsteroidExplosion(this);
        Global::world->addGameObject(e);
       
        this->assignAttribute(GameObject::DEAD);
    }
    else {
        setAngleRel(PI2 * (deltatime * spinSpeed));
        updatePosition(deltatime);
    }
    
    return nullptr;
}

void Asteroid::moveInDirection(float dist) {
    Transform::moveInDirection(dist);
    updatePosition(0.0f);
}

Asteroid::SIZES Asteroid::getSize() {
    return size;
}

void Asteroid::onDraw(olc::PixelGameEngine* pge) {
    if(decal == nullptr || sprite == nullptr) {
        Debug("WARNING: Asteroid " << this << " is missing sprite or decal");
        return;
    }

    pge->SetDrawTarget(layer_asteroids);
    SpaceObj::draw([this](RGNDS::Transform* tr){
        Global::pge->DrawRotatedDecal( 
            tr->pos, decal, tr->ang,
            {(float)sprite->width/2.0f,(float)sprite->height/2.0f},
            {tr->scale, tr->scale}
        );
    });
    pge->SetDrawTarget(nullptr);
#ifdef DEBUG_BUILD
    olc::vf2d moveDirection = getDirection();
    Global::pge->DrawLine(pos, pos+(moveDirection*moveVelocity), olc::GREEN);
#endif
}

std::vector<RGNDS::Collision::Circle> Asteroid::getColliders() {
    std::vector<RGNDS::Collision::Circle> r;

    for(auto t : renderer.getInstances())
        r.push_back({t.x, t.y, 28*scale});

    return r;
}

olc::Sprite* Asteroid::getSprite() { 
    if(sprite == nullptr) {
        Debug("WARNING: Asteroid " << this << " is missing sprite");
        return nullptr;
    }

    return sprite;
}

Asteroid::~Asteroid() { 
    if(decal != nullptr)  delete decal;
    if(sprite != nullptr) delete sprite;
}

void Asteroid::playSFX() {
    switch(rand()%2) {
        case 0: Mix_PlayChannel(-1, Assets::asteroid_hit_1, 0); break;
        case 1: Mix_PlayChannel(-1, Assets::asteroid_hit_2, 0); break;
    } 
}



void Asteroid::spawn(
    int nr, 
    SIZES size, 
    Ship* ship,
    int x, int y,
    olc::vf2d direction, float velocity
) {

    Debug("Asteroids: spawns " << nr << " asteroid(s) ");

    int spawned = 0;
    float sx=x, sy=y;

    if(nr > MAX_ASTEROIDS) 
        nr = MAX_ASTEROIDS;
    
    for(int a = 0; a < MAX_ASTEROIDS && spawned < nr; a++) {
        Asteroid* ast = new Asteroid(); 
        if(x == 0) sx = (rand()%APP_SCREEN_WIDTH);
        if(y == 0) sy = (rand()%APP_SCREEN_HEIGHT);

        ast->bringBackToLife(
                {sx, sy}, true, 
                size, 
                direction, velocity
        );

        if(ship) {
            ship->scale = 2.0f;
            RGNDS::Collision::Circle sc = ship->getCollider();
            ship->scale = 1.0f;

            while(RGNDS::Collision::checkCircleOnCircle(sc, ast->getColliders())) {
                Debug("ship hit before game started " << ast->pos.x << " " << ast->pos.y);
                ast->moveInDirection(32);
            }
        }

        Global::world->addGameObject(ast);
        spawned++;
    }
}

