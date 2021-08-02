#include "pausescreen.h"
#include "../config.h"
#include "../global.h"

PauseScreen::PauseScreen(Scene* backgroundProvider) {
    this->backgroundProvider = backgroundProvider;

    menu.transform.pos.x = 48;
    menu.transform.pos.y = 80;
    menu.transform.scale = 2.0f;
     
    menu.addOption("Resume");
    menu.addOption("Exit");
}

PauseScreen::~PauseScreen() {}

void PauseScreen::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {

    if(pge->GetKey(GameKeyMap[KEYPAD_DOWN]).bPressed)
        menu.selectNext();
    else if(pge->GetKey(GameKeyMap[KEYPAD_UP]).bPressed)
        menu.selectPrev();
    else if(pge->GetKey(olc::ENTER).bPressed 
            || pge->GetKey(GameKeyMap[KEYPAD_A]).bPressed)
        exit();

}

void PauseScreen::onDraw(olc::PixelGameEngine* pge) {
    this->backgroundProvider->onDraw(pge);

    pge->FillRect(
            76, 78 + (20 * menu.selected()),
            102 ,20,
            pix_menubg
    );
    menu.draw(pge);
}

bool PauseScreen::endGame() {
    return menu.selected() == 1;
}

void PauseScreen::onStart() { Global::pge->EnableLayer(layer_blackout, true); }
void PauseScreen::onEnd() { Global::pge->EnableLayer(layer_blackout, false); }

