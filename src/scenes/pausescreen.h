#pragma once

#include "../engine/olcPixelGameEngine.h"
#include "../engine/ui/TextMenu.h"

#include "./engine/Scene.h"

using namespace RGNDS;

class PauseScreen : public Scene {
public:
    PauseScreen(Scene* backgroundProvider);
    virtual~PauseScreen();

    bool onUpdate(olc::PixelGameEngine* pge, float deltaTime) override;
    void onDraw(olc::PixelGameEngine* pge) override;
    void onStart(olc::PixelGameEngine*) override;
    void onEnd() override;

    Scene* nextScene() override;

#ifdef DEBUG_BUILD
    bool skipLevel();
#endif

    bool endGame();

protected:
    Scene* backgroundProvider;

private:
    UI::TextMenu menu;

    std::string help_text;
    olc::vf2d   help_position;

};
