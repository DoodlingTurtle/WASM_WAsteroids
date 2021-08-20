#include "./titlescreen.h"
#include "global.h"
#include "config.h"
#include "gameobjects/asteroids.h"


TitleScreen::TitleScreen() 
{
    menu.transform.pos = Global::layout->titleScreen_menu_placement;
    menu.transform.scale = 2;

    help_placement = Global::layout->help_position;
    help_text = std::string("W = up   S = down   P = confirm");
    version_text = "alpha 0.2a";

    menu.addOption("new game");
    menu.addOption("help");
    menu.addOption("credits");
#ifdef DEBUG_BUILD
    menu.addOption("sound test");
#endif
}

void TitleScreen::onStart() {
    Global::world->removeWithAttribute(GameObject::ALL);    
    Asteroid::spawn(4);
}

void TitleScreen::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {

    if(Global::gameInput->pressed&KEYPAD_DOWN)
        menu.selectNext();
    else if(Global::gameInput->pressed&KEYPAD_UP)
        menu.selectPrev();
    else if(Global::gameInput->pressed&(KEYPAD_A))
        exit();
}

void TitleScreen::onDraw(olc::PixelGameEngine* pge) {

    pge->DrawString(Global::layout->titleScreen_title_placement, "WASteroids", olc::WHITE, 3.0f);
    pge->FillRect(
            Global::layout->titleScreen_menu_placement.x+28, 
            (Global::layout->titleScreen_menu_placement.y-2) + (20 * menu.selected()),
            134, 20,
            pix_menubg
    );

    menu.draw(pge);

    pge->DrawStringDecal({4, 4}, version_text, olc::WHITE, { 0.75f, 0.75f });
    pge->DrawString(help_placement, help_text);
}
void TitleScreen::onEnd() { Global::world->removeWithAttribute(GameObject::ALL); }

int TitleScreen::selectedMenu(){ return menu.selected(); }
