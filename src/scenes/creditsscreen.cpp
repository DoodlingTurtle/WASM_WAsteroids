#include "creditsscreen.h"

CreditsScreen::CreditsScreen() {
    spr = nullptr;
}
CreditsScreen::~CreditsScreen() {
    if(spr != nullptr)
        delete spr;
}

void CreditsScreen::onStart() {
    spr = new olc::Sprite("assets/credits.png");
}
void CreditsScreen::onEnd() {
    delete spr;
}

void CreditsScreen::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {
    if(   pge->GetKey(olc::ENTER).bPressed
       || pge->GetKey(GameKeyMap[KEYPAD_A]).bPressed
    ) exit();
}

void CreditsScreen::onDraw(olc::PixelGameEngine* pge) {
    pge->DrawSprite(0, 0, spr);
}
