#include "titlescreen.h"
#include "../global.h"
#include "../config.h"


TitleScreen::TitleScreen() 
{
    menu.transform.pos.y = 272;
    menu.transform.pos.x = 32;
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

    if(pge->GetKey(GameKeyMap[KEYPAD_DOWN]).bPressed)
        menu.selectNext();
    else if(pge->GetKey(GameKeyMap[KEYPAD_UP]).bPressed)
        menu.selectPrev();
    else if(pge->GetKey(olc::ENTER).bPressed 
            || pge->GetKey(GameKeyMap[KEYPAD_A]).bPressed)
        exit();
}

void TitleScreen::onDraw(olc::PixelGameEngine* pge) {
    Global::asteroids->draw();

    pge->DrawString(10, 88, "WASteroids", olc::WHITE, 3.0f);
    pge->FillRect(
            60, 270 + (20 * menu.selected()),
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

