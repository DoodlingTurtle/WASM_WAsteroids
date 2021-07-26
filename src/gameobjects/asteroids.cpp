#include "asteroids.h"
#include "../config.h"
#include "../global.h"

#include "scorepopup.h"

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

        olc::Pixel col(138, 100, 73, 255);

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
                    col
            );
        }

	pge->SetDrawTarget(nullptr);
}


void Asteroids::Asteroid::bringBackToLife(
        olc::vf2d pos, bool generateNewShape, 
        Asteroids::SIZES size
) 
{

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
}
std::vector<SpaceObj*>* Asteroids::Asteroid::onUpdate(float deltatime) {

    if(killOnNextUpdate) {

        std::vector<SpaceObj*>* spa;

        if(this->size != Asteroids::SIZE_SMALL) {
            spa = (std::vector<SpaceObj*>*)Global::asteroids->spawnAsteroids( 2,  
                   static_cast<Asteroids::SIZES>(
                       static_cast<int>(this->size)-1
                    ), this->pos.x, this->pos.y);
        }
        else spa = new std::vector<SpaceObj*>();

        Global::score += 100/scale;

        //TODO: spawn score number
        spa->push_back(ScorePopup::spawn(100/scale, pos.x, pos.y));
        //TODO: Spawn AsteroidExplosion at go->pos
        //(once particle system is reintroduced)
        this->kill();
        Global::asteroids->markDirty();
        return spa;
    }
    else {
        setAngleRel(PI2 * (deltatime * spinSpeed));
        updatePosition(deltatime);
    }
    

    //TODO: Reintroduce Spaceship collision
    return nullptr;
}


Asteroids::SIZES Asteroids::Asteroid::getSize() {
    return size;
}

void Asteroids::Asteroid::onDraw(olc::PixelGameEngine* pge) {
    SpaceObj::draw([this](RGNDS::Transform* tr){
        olc::GFX2D::Transform2D tra;
        tr->toTransform2D(32, 32, &tra);
        olc::GFX2D::DrawSprite(sprite, tra); 
    });
}
Asteroids::Asteroid::~Asteroid() { delete sprite; }


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
            asteroids[a].onDraw(nullptr);
		
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

void Asteroids::killall() {
    Debug("Killall asteroids" << asteroids);
	for(int a = 0; a < MAX_ASTEROIDS; a++) {
        Debug("check asteroid " << a << ": " << asteroids[a].isAlive());
        if(asteroids[a].isAlive())
            asteroids[a].kill();
    }

    dirty = true;
}

