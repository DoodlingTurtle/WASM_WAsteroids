#include "titlescreen.h"
#include "../global.h"
#include "../config.h"


TitleScreen::TitleScreen() 
{
    menu.transform.pos = Global::layout->titleScreen_menu_placement;
    menu.transform.scale = 2;

    menu.addOption("new game");
    menu.addOption("options");
    menu.addOption("credits");
}

void TitleScreen::onStart() {
    Global::asteroids->spawnAsteroids(4);
}

void TitleScreen::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {
    Global::asteroids->update(deltaTime);

    if(Global::gameInput->pressed&KEYPAD_DOWN)
        menu.selectNext();
    else if(Global::gameInput->pressed&KEYPAD_UP)
        menu.selectPrev();
    else if(Global::gameInput->pressed&(KEYPAD_A|KEYPAD_START))
        exit();
}

void TitleScreen::onDraw(olc::PixelGameEngine* pge) {
    Global::asteroids->draw();

    pge->DrawString(Global::layout->titleScreen_title_placement, "WASteroids", olc::WHITE, 3.0f);
    pge->FillRect(
            Global::layout->titleScreen_menu_placement.x+28, 
            (Global::layout->titleScreen_menu_placement.y-2) + (20 * menu.selected()),
            134, 20,
            pix_menubg
    );

    menu.draw(pge);
}
void TitleScreen::onEnd() {
    Global::asteroids->killall();
}

int TitleScreen::selectedMenu(){
    return menu.selected();
}

