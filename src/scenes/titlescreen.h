#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "../olcPixelGameEngine.h"
#include "../scene.h"
#include "../gameobjects/asteroids.h"

#include "../textmenu.h"

class TitleScreen : public Scene {

public:
    TitleScreen();

	void onUpdate(olc::PixelGameEngine* pge, float dt) override;
	void onDraw(olc::PixelGameEngine* pge) override;

    int selectedMenu();

protected:
    void onStart() override;
    void onEnd() override;
private:
    TextMenu menu;
};

#endif
