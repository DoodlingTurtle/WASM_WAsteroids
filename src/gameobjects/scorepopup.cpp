#include "scorepopup.h"
#include <cstdio>

ScorePopup::ScorePopup(short s, float x, float y) {
    score = s;       
    lifetime = 45;   //45 ticks = 1.5 Sec @ 30 FPS
    pos.x = x;
    pos.y = y;
    bIsAlive = true;
}

bool ScorePopup::bDirty = false;
void ScorePopup::refreshInstanceList() {
    if(bDirty) {
        ScorePopup* sp;
        for(int a = _instances.size()-1; a >= 0; a--) {
            sp = _instances.at(a);
            
            if(sp->isAlive()) continue;

            delete sp;
            _instances.erase(_instances.begin()+a);
        }

        bDirty = false;
    }
}

ScorePopup::~ScorePopup() {}

std::vector<ScorePopup*> ScorePopup::_instances = std::vector<ScorePopup*>();

static olc::Pixel color[2] = {
    olc::Pixel(255, 0, 0),
    olc::Pixel(0, 255, 0)
};

void ScorePopup::cleanup(){
    for(auto s : _instances)
        delete s;

    _instances.clear();
}

ScorePopup* ScorePopup::spawn(short score, float x, float y) {

    ScorePopup* s = new ScorePopup(score, x, y);
    _instances.push_back(s);

    return s;
}

std::vector<SpaceObj*>* ScorePopup::onUpdate(float deltaTime) {  
    this->lifetime--;
    this->pos.y -= 20.0f*deltaTime;
    if(this->lifetime==0)
        this->kill();

    return nullptr;
}

void ScorePopup::kill() {
    SpaceObj::kill();
    this->bDirty = true;
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
