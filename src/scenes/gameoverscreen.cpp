#include <cstdio>
#include "./gameoverscreen.h"

#include "../engine/Global.h"
#include "../engine/Assets.h"
#include "../core/DebugOverlay.h"

#include "./titlescreen.h"

void GameOverScreen::onStart() { 
    scoreLocation = { 117, 5 };

    //TODO: Reimplement with new Engine
    /*
    RGNDS::Lerp<olc::vf2d>* lerp = new RGNDS::Lerp<olc::vf2d>(&scoreLocation);
    lerp->changeTarget(
        olc::vf2d{ 64, 88 } + Global::layout->screen_offset, 
        1.5f
    );
    timeline.addStrip(lerp, 0.0f, 0);
*/

/*
    if (Global::recordScore < Global::score)
        Assets::record->drawDecal(pge, scoreLocation + olc::vf2d{ 146, 2 });
*/
    Assets::record->playRange(0, 10, true);
    Assets::record->changeTint(olc::RED);


#ifdef DEBUG_BUILD 
	DebugOverlay* overlay = new DebugOverlay();
	overlay->addItem("RecordScore", DebugOverlay::TYPE_INT, &Global::recordScore);
	overlay->addItem("RecordLevel", DebugOverlay::TYPE_INT, &Global::recordLevel);
	Global::world.addGameObject(overlay);
#endif

}

void GameOverScreen::onEnd() {
    // Update records
    Global::recordLevel = std::max(Global::recordLevel, Global::level);
    Global::recordScore = std::max(Global::recordScore, Global::score);

    Global::world.removeWithAttribute(GameObject::DEBUG);
    
    Global::switchBGMusic(Assets::bgmMenu);

}

bool GameOverScreen::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {
    if (Global::input.released & KEYPAD_A)
        return false;

    timeline.onUpdate(deltaTime);
    Assets::record->onUpdate(deltaTime);

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

    timeline.onDraw(pge);

    /*
    if (lerp.finished()) {
        pge->DrawStringDecal(
            scoreLocation + olc::vf2d{ -16.0f, 24.0f },
            "Level reached: " + _prepNum("% 3d", 4, Global::level),
            olc::WHITE
        );
    }
    */
    pge->DrawStringDecal(olc::vf2d{ 40, 296} + Global::layout->screen_offset, "  Press P  ", olc::WHITE, {2.0f, 2.0f});
    pge->DrawStringDecal(olc::vf2d{ 82, 312} + Global::layout->screen_offset, "to continue", olc::WHITE, {1.0f, 1.0f});
}

Scene* GameOverScreen::nextScene() { return new TitleScreen(); }
