#include "loadscreen.h"
#include "../assets.h"
#include "../global.h"


LoadScreen::LoadScreen()
:msg(" loading ... ")
{}

LoadScreen::~LoadScreen() {}

void LoadScreen::onUpdate(olc::PixelGameEngine *pge, float deltaTime){
    if(Assets::init(&msg)) exit(); 
}

void LoadScreen::onDraw(olc::PixelGameEngine *pge) {
    pge->DrawString(4, 4, msg, olc::WHITE);
}

void LoadScreen::onEnd() { Global::switchBGMusic(Assets::bgmMenu); };
