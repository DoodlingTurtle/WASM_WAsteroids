#include "./gameoverscreen.h"

#include <cstdio>
#include "global.h"
#include "assets.h"
#include "DebugOverlay.h"


void GameOverScreen::onStart() { 
    scoreLocation = { 117, 5 };

    lerp = RGNDS::Lerp<olc::vf2d>(&scoreLocation);
    lerp.changeTarget(
        olc::vf2d{ 64, 88 } + Global::layout->screen_offset, 
        1.5f
    );

#ifdef DEBUG_BUILD 
	DebugOverlay* overlay = new DebugOverlay();
	overlay->addItem("RecordScore", DebugOverlay::TYPE_INT, &Global::recordScore);
	overlay->addItem("RecordLevel", DebugOverlay::TYPE_INT, &Global::recordLevel);
	Global::world->addGameObject(overlay);
#endif

}

void GameOverScreen::onEnd() {
    // Update records
    Global::recordLevel = std::max(Global::recordLevel, Global::level);
    Global::recordScore = std::max(Global::recordScore, Global::score);

    Global::world->removeWithAttribute(GameObject::DEBUG);
    
    Global::switchBGMusic(Assets::bgmMenu);

}

void GameOverScreen::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {
    if(Global::gameInput->released&KEYPAD_A)
        exit();

    lerp.update(deltaTime);
}

static std::string _prepNum(const char* pat, int digits, int num) {
    std::string s = std::to_string(num);
    int fillDigits = digits - s.length();
    if (fillDigits > 0)
        s = std::string(fillDigits, ' ') + s;

    return s;
}

void GameOverScreen::onDraw(olc::PixelGameEngine* pge) {
    pge->DrawStringDecal(scoreLocation, 
        _prepNum("% 8d", 9, Global::score),
		olc::Pixel{32, 32, 196}
        , { 2.0f, 2.0f }
	);

    if (lerp.finished()) {
        pge->DrawStringDecal(
            scoreLocation + olc::vf2d{ -16.0f, 24.0f },
            "Level reached: " + _prepNum("% 3d", 4, Global::level),
            olc::WHITE
        );
    }

    pge->DrawStringDecal(olc::vf2d{ 40, 296} + Global::layout->screen_offset, "  Press P  ", olc::WHITE, {2.0f, 2.0f});
    pge->DrawStringDecal(olc::vf2d{ 82, 312} + Global::layout->screen_offset, "to continue", olc::WHITE, {1.0f, 1.0f});
}


