#include "asteroids.h"
#include "../config.h"
#include "../global.h"

#include "scorepopup.h"
#include "../particles/asteroid_particles.h"

#include <stdio.h>
using namespace std;

Asteroids::Asteroid::Asteroid() : SpaceObj(32.0f)
{ 
    sprite = new olc::Sprite(64, 64); 
    killOnNextUpdate = false;
}

void Asteroids::Asteroid::markAsHit() { killOnNextUpdate = true; }


float _getradius() {
    return 22 + rand()%10;
}

void Asteroids::Asteroid::generateShape() {
    olc::PixelGameEngine* pge = Global::pge;

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
    if(decal == nullptr)
        decal = new olc::Decal(sprite);
    else
        decal->UpdateSprite();
}


void Asteroids::Asteroid::bringBackToLife(
        olc::vf2d pos, bool generateNewShape, 
        Asteroids::SIZES size
) 
{

    Debug("revive Asteroid " << this);

    setAngle(RandF() * PI2);
    velocity.x = rand()%10; // velocity is up to 10 px per second
    velocity.y = rand()%10;
    spinSpeed = (RandF() * 0.5 + 0.5) * 0.0625; // Spin by 360� every 16 Seconds (at max spinspeed)

    this->pos.x = pos.x;
	this->pos.y = pos.y;

    this->size = size;
    if(size == SIZE_RANDOM) 
        size = static_cast<Asteroids::SIZES>(rand()%3);

    switch(size) {
        case Asteroids::SIZE_SMALL: {
            this->scale = 0.25f; break; }
                                    
        case Asteroids::SIZE_MIDDLE: {
            this->scale = 0.5f; break; }

        case Asteroids::SIZE_LARGE: 
        default: {
            this->scale = 1.0f; break; }
    }

    if(generateNewShape)
        generateShape();

    bIsAlive = true;
    killOnNextUpdate = false;

    updatePosition(0.0f);

}
std::vector<SpaceObj*>* Asteroids::Asteroid::onUpdate(float deltatime) {

    if(killOnNextUpdate) {

        std::vector<SpaceObj*>* spa;

        if(this->size != Asteroids::SIZE_SMALL) {
            spa = (std::vector<SpaceObj*>*)Global::asteroids->spawnAsteroids( 2,  
                   static_cast<Asteroids::SIZES>(
                       static_cast<int>(this->size)-1
                    ), this->pos.x, this->pos.y);

            for(SpaceObj* a : *spa)
               a->moveInDirection(24.0f*this->scale); 
        }
        else spa = new std::vector<SpaceObj*>();

        Global::score += 100/scale;

        spa->push_back(ScorePopup::spawn(100/scale, pos.x, pos.y));
        
        //Spawn AsteroidExplosion at go->pos
        Asteroid_Particle_Emitter* e 
            = new Asteroid_Particle_Emitter(this->pos.x, this->pos.y, this->scale);
        Asteroid_Particle* p = new Asteroid_Particle(e);
        if(!Global::particleSystem->assign(e, p)) {
            Debug("Failed to assign PS");
            delete e;
            delete p;
        }
        else {
            spa->push_back(e);
        }
        
        this->kill();
        Global::asteroids->markDirty();
        return spa;
    }
    else {
        setAngleRel(PI2 * (deltatime * spinSpeed));
        updatePosition(deltatime);
    }
    
    return nullptr;
}

void Asteroids::Asteroid::moveInDirection(float dist) {
    Transform::moveInDirection(dist);
    updatePosition(0.0f);
}

Asteroids::SIZES Asteroids::Asteroid::getSize() {
    return size;
}

void Asteroids::Asteroid::onDraw(olc::PixelGameEngine* pge) {
    pge->SetDrawTarget(layer_asteroids);
    SpaceObj::draw([this](RGNDS::Transform* tr){
        Global::pge->DrawRotatedDecal( 
            tr->pos, decal, tr->ang,
            {(float)sprite->width/2.0f,(float)sprite->height/2.0f},
            {tr->scale, tr->scale}
        );
    });
    pge->SetDrawTarget(nullptr);
}

std::vector<RGNDS::Collision::Circle> Asteroids::Asteroid::getColliders() {
    std::vector<RGNDS::Collision::Circle> r;

    for(auto t : renderer.getInstances())
        r.push_back({t.x, t.y, 28*scale});

    return r;
}

Asteroids::Asteroid::~Asteroid() { 
    delete decal;
    delete sprite;
}


/*#############################################################################
 * Asteroids
 *###########################################################################*/

Asteroids::Asteroids() 
: dirty(true)
{}

void Asteroids::update(float deltaTime) {
	for(int a = 0; a < MAX_ASTEROIDS; a++) 
        if(asteroids[a].isAlive())
            asteroids[a].onUpdate(deltaTime);
}

void Asteroids::draw() {
	int a; 
	for(a = 0; a < MAX_ASTEROIDS; a++) 
		if(asteroids[a].isAlive())
            asteroids[a].onDraw(Global::pge);
		
}

void Asteroids::markDirty() { dirty = true; }

std::vector<Asteroids::Asteroid*> Asteroids::getLiveAsteroids() {
    if(dirty) {
        liveAsteroids.clear();
        for(int a = 0; a < MAX_ASTEROIDS; a++) {
            if(asteroids[a].isAlive())
                liveAsteroids.push_back(&asteroids[a]);
        }
        dirty = false;
    }

    return liveAsteroids;
}

vector<Asteroids::Asteroid*>* Asteroids::spawnAsteroids(
        int nr, 
        Asteroids::SIZES size, 
        int x, int y
    ) {


    Debug(this << " spawns " << nr << " asteroid(s) ");

    int spawned = 0;
    vector<Asteroids::Asteroid*>* list = new vector<Asteroids::Asteroid*>();
    float sx=x, sy=y;

    if(nr > MAX_ASTEROIDS) 
        nr = MAX_ASTEROIDS;
    
    for(int a = 0; a < MAX_ASTEROIDS && spawned < nr; a++) {

        if(!asteroids[a].isAlive()) {

            if(x == 0)              sx = (rand()%APP_SCREEN_WIDTH);
            if(y == 0)              sy = (rand()%APP_SCREEN_HEIGHT);

            asteroids[a].bringBackToLife( 
                    {sx, sy}, 
                    true, 
                    size
            );
            list->push_back(&asteroids[a]);
            spawned++;
        }
    }

    dirty = true;

    return list;
}

Asteroids::Asteroid* Asteroids::isAsteroid(void* go) {
    Asteroids::Asteroid* ret = nullptr;
    if(go >= asteroids && go < (&asteroids[MAX_ASTEROIDS-1]))
        ret = (Asteroids::Asteroid*)go;
    
    return ret;
}

std::vector<RGNDS::Collision::Circle> Asteroids::getActiveColliders() {
    std::vector<RGNDS::Collision::Circle> c;

	for(int a = 0; a < MAX_ASTEROIDS; a++) {
        if(asteroids[a].isAlive()) {
            std::vector<RGNDS::Collision::Circle> ac = asteroids[a].getColliders();
            c.insert(c.end(), ac.begin(), ac.end());
        }
    }

    return c;
};

void Asteroids::killall() {
    Debug("Killall asteroids" << asteroids);
	for(int a = 0; a < MAX_ASTEROIDS; a++) {
        if(asteroids[a].isAlive())
            asteroids[a].kill();
    }

    dirty = true;
}
