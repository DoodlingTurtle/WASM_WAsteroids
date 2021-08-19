#include "./scorepopup.h"
#include <cstdio>

ScorePopup::ScorePopup(short s, float x, float y) {
    score = s;       
    lifetime = 1000;   //1000ms ms = 1 Sec
    pos.x = x;
    pos.y = y;
    bIsAlive = true;
}

ScorePopup::~ScorePopup() {}

static olc::Pixel color[2] = {
    olc::Pixel(255, 0, 0),
    olc::Pixel(0, 255, 0)
};


std::vector<SpaceObj*>* ScorePopup::onUpdate(float deltaTime) {  
    this->lifetime -= 1000 * deltaTime;
    this->pos.y -= 20.0f*deltaTime;
    if(this->lifetime<=0)
        this->kill();

    return nullptr;
}

void ScorePopup::onDraw(olc::PixelGameEngine* pge) {
    char buffer[7];
    sprintf(buffer, "%d", this->score);
    std::string s(buffer);
    
    pge->DrawString(
            pos.x, pos.y, 
            s, color[this->lifetime&1]
    ); 
};

bool ScorePopup::allowDeleteAfterDeath() { return true; }
