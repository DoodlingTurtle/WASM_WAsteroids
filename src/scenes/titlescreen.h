#pragma once

#include "../engine/olcPixelGameEngine.h"
#include "../engine/Scene.h"
#include "../engine/ui/textmenu.h"

using namespace RGNDS;

class TitleScreen : public Scene {

public:
    TitleScreen();

	bool onUpdate(olc::PixelGameEngine* pge, float dt) override;
	void onDraw(olc::PixelGameEngine* pge) override;

    Scene* nextScene() override;

    int selectedMenu();

protected:
    void onStart(olc::PixelGameEngine*) override;
    void onEnd() override;

private:
    olc::vf2d help_placement;
    std::string help_text;
    std::string version_text;
    UI::TextMenu menu;
};
