#include "./pausescreen.h"
#include "../config.h"
#include "../engine/Global.h"
#include "../engine/Assets.h"

#include "./titlescreen.h"
#include "./upgradescreen.h"
#include "./gameoverscreen.h"

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
     
    if(Global::input->pressed&KEYPAD_DOWN)
        menu.selectNext();
    else if(Global::input->pressed&KEYPAD_UP)
        menu.selectPrev();
    else if(Global::input->released&(KEYPAD_A))
        return false;

    return true;
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

void PauseScreen::onStart(olc::PixelGameEngine* pge) { 
    Global::game->pause();
    Global::game->EnableLayer(layer_blackout, true); }

void PauseScreen::onEnd() { 
    Global::game->resume();
    Global::game->EnableLayer(layer_blackout, false); }

Scene* PauseScreen::nextScene() {

    int sel = menu.selected();

    if (sel != 0 && sel != 2)
        delete backgroundProvider;

    switch (menu.selected()) {

    case 0: /* resume */
        return backgroundProvider;

    case 1: /* exit */
        switchBGMusic(Assets::bgmMenu);
        return new TitleScreen();

    case 2: /* Skip Level */
        return new UpgradeScreen((MainGameScreen*)backgroundProvider);

    case 3: /* game over */
        Global::score = 523346;
        Global::level = 893;
        return new GameOverScreen();

    }

    return nullptr;
}

