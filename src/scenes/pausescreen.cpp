#include "./pausescreen.h"
#include "../config.h"
#include "../engine/Global.h"
#include "../engine/Assets.h"
using namespace RGNDS;

PauseScreen::PauseScreen(Scene* backgroundProvider) {
    this->backgroundProvider = backgroundProvider;

    menu.transform.pos = olc::vf2d{ 48, 80 } + Global::layout->screen_offset;
    menu.transform.scale = 2.0f;

    help_text = "W = up   S = down  P = confirm";
    help_position = Global::layout->help_position;

    menu.addOption("Resume");
    menu.addOption("Exit");
#ifdef DEBUG_BUILD
    menu.addOption("[D] next Level");
    menu.addOption("[D] instand lose");
#endif
}

PauseScreen::~PauseScreen() {}

bool PauseScreen::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {
     
    if(Global::input.pressed&KEYPAD_DOWN)
        menu.selectNext();
    else if(Global::input.pressed&KEYPAD_UP)
        menu.selectPrev();
    else if(Global::input.released&(KEYPAD_A))
        return false;
}

void PauseScreen::onDraw(olc::PixelGameEngine* pge) {
    this->backgroundProvider->onDraw(pge);

    pge->FillRectDecal(
        olc::vf2d{ 76.0f, 78.0f + (20.0f * menu.selected()) } + Global::layout->screen_offset,
        { 102 ,20 }, pix_menubg
    );
    menu.draw(pge);

    pge->DrawStringDecal(help_position, help_text, olc::WHITE);
}

bool PauseScreen::endGame() {
    return menu.selected() == 1;
}
#ifdef DEBUG_BUILD
bool PauseScreen::skipLevel() {
    return menu.selected() == 2;
}
#endif

void PauseScreen::onStart() { Global::pge->EnableLayer(layer_blackout, true); }
void PauseScreen::onEnd() { 
    Global::pge->EnableLayer(layer_blackout, false); 
    
    if (menu.selected() == 1) 
        Global::switchBGMusic(Assets::bgmMenu);
#ifdef DEBUG_BUILD
    if (menu.selected() == 3) {
        Global::score += 523346;
        Global::level += 893;
        (*(Global::world.findByAttribute(GameObject::PLAYER_SHIP).begin()))->assignAttribute(GameObject::DEAD); 
        menu.setSelection(0);
    }
#endif
}

Scene* PauseScreen::nextScene() {
    return nullptr;
    //TODO: replace with propper content
}

