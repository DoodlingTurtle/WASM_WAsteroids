#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "../olcPixelGameEngine.h"
#include "../scene.h"
#include "../asteroids.h"

#include "../textmenu.h"

class TitleScreen : public Scene {

public:
    void onStart() override;
	void onUpdate(olc::PixelGameEngine* pge, float dt) override;
	void onDraw(olc::PixelGameEngine* pge) override;
    void onEnd() override;

private:
    TextMenu menu;
};

#endif
