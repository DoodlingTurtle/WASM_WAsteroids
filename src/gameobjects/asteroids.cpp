#include "../config.h"
#include "asteroids.h"

#include <stdio.h>
using namespace std;

Asteroids::Asteroid::Asteroid() : SpaceObj(32.0f)
{ sprite = new olc::Sprite(64, 64); }

void Asteroids::Asteroid::init(olc::PixelGameEngine* pge) 
{ /*TODO: delete if not needed later*/ }

float _getradius() {
    return 22 + rand()%10;
}
void Asteroids::Asteroid::generateShape(olc::PixelGameEngine* pge) {

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
        olc::PixelGameEngine* pge, 
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
        generateShape(pge);

    bIsAlive = true;
}
void Asteroids::Asteroid::onUpdate(float deltatime) {
    setAngleRel(PI2 * (deltatime * spinSpeed));
    updatePosition(deltatime);

    //TODO: Reintroduce Spaceship collision
}


short Asteroids::Asteroid::getScoreValue() {
    return 100/scale;
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
void Asteroids::init(olc::PixelGameEngine* pge){
    this->pge = pge;
	for(int a = 0; a < MAX_ASTEROIDS; a++) 
		asteroids[a].init(pge);
}

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


 vector<Asteroids::Asteroid*>* Asteroids::spawnAsteroids(
        int nr, 
        Asteroids::SIZES size, 
        int x, int y
    ) {

    int spawned = 0;
    vector<Asteroids::Asteroid*>* list = new vector<Asteroids::Asteroid*>();
    float sx=x, sy=y;

    if(nr > MAX_ASTEROIDS) 
        nr = MAX_ASTEROIDS;
    
    for(int a = 0; a < MAX_ASTEROIDS && spawned < nr; a++) {

        if(x == 0)              sx = (rand()%APP_SCREEN_WIDTH);
        if(y == 0)              sy = (rand()%APP_SCREEN_HEIGHT);

        if(!asteroids[a].isAlive()) {
            asteroids[a].bringBackToLife( 
                    pge, 
                    {sx, sy}, 
                    true, 
                    size
            );
            list->push_back(&asteroids[a]);
            spawned++;
        }
    }
    return list;
}

Asteroids::Asteroid* Asteroids::isAsteroid(void* go) {
    Asteroids::Asteroid* ret = nullptr;
    if(go >= asteroids && go < (&asteroids[MAX_ASTEROIDS-1]))
        ret = (Asteroids::Asteroid*)go;
    
    return ret;
}

void Asteroids::killall() {
	for(int a = 0; a < MAX_ASTEROIDS; a++) 
        if(asteroids[a].isAlive())
            asteroids[a].kill();
}

