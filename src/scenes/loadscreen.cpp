#include "./loadscreen.h"
#include "../engine/Assets.h"
#include "../engine/Global.h"

#include "../scenes/titlescreen.h"

using namespace RGNDS;

LoadScreen::LoadScreen()
:msg(" loading ... ")
{}

LoadScreen::~LoadScreen() {}

bool LoadScreen::onUpdate(olc::PixelGameEngine *pge, float deltaTime){
    return !Assets::init(&msg); 
}

void LoadScreen::onDraw(olc::PixelGameEngine *pge) {
    pge->DrawString(4, 4, msg, olc::WHITE);
}

void LoadScreen::onEnd() { 
    Assets::record->setup({ 72, 12 }, 30.0f);
    Global::switchBGMusic(Assets::bgmMenu);
};

Scene* LoadScreen::nextScene() { return new TitleScreen(); }
