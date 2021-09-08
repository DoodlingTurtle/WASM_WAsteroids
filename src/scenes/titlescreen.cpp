#include "./titlescreen.h"
#include "../engine/Global.h"
#include "../engine/Assets.h"

#include "../config.h"
#include "../gameobjects/asteroids.h"

#include "./soundtest.h"
#include "./textscene.h"
#include "./maingame.h"

using namespace RGNDS;

TitleScreen::TitleScreen() 
{
    menu.transform.pos = Global::layout->titleScreen_menu_placement;
    menu.transform.scale = 2;

    help_placement = Global::layout->help_position;
    help_text = std::string("W = up   S = down   P = confirm");
    version_text = "alpha 0.8";

    menu.addOption("new game");
    menu.addOption("help");
    menu.addOption("credits");
#ifndef OLC_PLATFORM_EMSCRIPTEN
    menu.addOption("quit");
#endif
#ifdef DEBUG_BUILD
    menu.addOption("sound test");
#endif
}

void TitleScreen::onStart(olc::PixelGameEngine* pge) {
    Global::world->removeWithAttribute(GameObject::ALL);    
    Asteroid::spawn(5);
}

bool TitleScreen::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {

    if (Global::input->pressed & KEYPAD_DOWN)
        menu.selectNext();
    else if (Global::input->pressed & KEYPAD_UP)
        menu.selectPrev();
    else if (Global::input->pressed & (KEYPAD_A))
        return false;

    return true;
}

void TitleScreen::onDraw(olc::PixelGameEngine* pge) {


    pge->DrawString(Global::layout->titleScreen_title_placement, "WASteroids", olc::WHITE, Global::layout->titleScreen_title_scale);
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

Scene* TitleScreen::nextScene() {
    switch (menu.selected()) {
    case 0: return new MainGameScreen(); break;
    case 1: return new TextScene("help.txt"); break;
    case 2: return new TextScene("credits.txt"); break;
    case 3: return nullptr; break;
    case 4: return new SoundTest(); break;
    }

    return nullptr;
}
