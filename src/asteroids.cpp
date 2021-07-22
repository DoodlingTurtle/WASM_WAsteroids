#include "config.h"
#include "asteroids.h"

#include <stdio.h>
using namespace std;

Asteroid::Asteroid() : SpaceObj(32.0f)
{ sprite = new olc::Sprite(64, 64); }

void Asteroid::init(olc::PixelGameEngine* pge) 
{ /*TODO: delete if not needed later*/ }

float _getradius() {
    return 22 + rand()%10;
}
void Asteroid::generateShape(olc::PixelGameEngine* pge) {

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
            
            pge->FillTriangle(32, 32, 32 + x, 32 + y, 32 + x1, 32 + y1, olc::DARK_YELLOW);
        }

	pge->SetDrawTarget(nullptr);
}

void Asteroid::bringBackToLife(olc::PixelGameEngine* pge, olc::vf2d pos, bool generateNewShape, float scale) 
{

    setAngle(RandF() * PI2);
    velocity.x = rand()%10; // velocity is up to 10 px per second
    velocity.y = rand()%10;
    spinSpeed = (RandF() * 0.5 + 0.5) * 0.0625; // Spin by 360� every 16 Seconds (at max spinspeed)

    this->pos.x = pos.x;
	this->pos.y = pos.y;
    this->scale = scale;

    if(generateNewShape)
        generateShape(pge);

    bIsAlive = true;
}
void Asteroid::onUpdate(float deltatime) {
    setAngleRel(PI2 * (deltatime * spinSpeed));
    updatePosition(deltatime);

    //TODO: Reintroduce Spaceship collision
}


short Asteroid::getScoreValue() {
    return 100/scale;
}

void Asteroid::onDraw(SpaceObj::MainGameDrawData* data) {
    SpaceObj::draw([this](RGNDS::Transform* tr){
        olc::GFX2D::Transform2D tra;
        tr->toTransform2D(32, 32, &tra);
        olc::GFX2D::DrawSprite(sprite, tra); 
    });
}
Asteroid::~Asteroid() { delete sprite; }


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


 vector<Asteroid*>* Asteroids::spawnAsteroids(
        int nr, 
        Asteroids::SIZES size, 
        int x, int y
    ) {

    int spawned = 0;
    vector<Asteroid*>* list = new vector<Asteroid*>();
    float sx=x, sy=y;
    float scale = 1.0f;

    if(nr > MAX_ASTEROIDS) 
        nr = MAX_ASTEROIDS;

    switch(size){
        case SIZE_MIDDLE: scale = 0.5f; break;
        case SIZE_SMALL:  scale = 0.25f; break;
    }
    
    for(int a = 0; a < MAX_ASTEROIDS && spawned < nr; a++) {


        if(size == SIZE_RANDOM) scale = 1.0f / (float)(1<<(rand()%3));
        if(x == 0)              sx = (rand()%APP_SCREEN_WIDTH);
        if(y == 0)              sy = (rand()%APP_SCREEN_HEIGHT);

        if(!asteroids[a].isAlive()) {
            asteroids[a].bringBackToLife( 
                    pge, 
                    {sx, sy}, 
                    true, 
                    scale  
            );
            list->push_back(&asteroids[a]);
            spawned++;
        }
    }
    return list;
}

void Asteroids::killall() {
	for(int a = 0; a < MAX_ASTEROIDS; a++) 
        if(asteroids[a].isAlive())
            asteroids[a].kill();
}

