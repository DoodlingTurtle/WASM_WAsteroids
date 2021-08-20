#include "./scorepopup.h"
#include <cstdio>

ScorePopup::ScorePopup(short s, float x, float y) 
:GameObject({
    GameObject::SPACE_OBJ_DRAW,
    GameObject::SPACE_OBJ_UPDATE
        })
, score(s), lifetime(1000)
{
    pos = {x, y};
}

static olc::Pixel color[2] = {
    olc::Pixel(255, 0, 0),
    olc::Pixel(0, 255, 0)
};

std::vector<SpaceObj*>* ScorePopup::onUpdate(float deltaTime) {  
    this->lifetime -= 1000 * deltaTime;
    this->pos.y -= 20.0f*deltaTime;
    if(this->lifetime<=0)
        assignAttribute(GameObject::DEAD);

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
