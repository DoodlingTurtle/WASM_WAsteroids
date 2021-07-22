#include "titlescreen.h"

void TitleScreen::onStart() {
    asteroids->spawnAsteroids(4);

    menu.transform.pos.y = 272;
    menu.transform.pos.x = 32;
    menu.transform.scale = 2;

    menu.addOption("new game");
    menu.addOption("options");
    menu.addOption("credits");
}

void TitleScreen::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {
    asteroids->update(deltaTime);

    if(pge->GetKey(GameKeyMap[KEYPAD_DOWN]).bPressed)
        menu.selectNext();
    else if(pge->GetKey(GameKeyMap[KEYPAD_UP]).bPressed)
        menu.selectPrev();
//    else if(press&(KEY_START|KEY_A))
//        exit();
}

void TitleScreen::onDraw(olc::PixelGameEngine* pge) {
    asteroids->draw();

    pge->DrawString(10, 88, "WASteroids", olc::WHITE, 3.0f);
    pge->FillRect(
            60, 270 + (20 * menu.selected()),
            134, 20,
            pix_menubg
    );

    menu.draw(pge);
}
void TitleScreen::onEnd() {
    asteroids->killall();
}

