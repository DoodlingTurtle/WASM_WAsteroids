#include <cstdio>
#include "./gameoverscreen.h"

#include "../engine/Global.h"
#include "../engine/Assets.h"
#include "../engine/ui/DebugOverlay.h"

#include "./titlescreen.h"
#include "../config.h"

#include "../engine/animation/strips/LerpStrip.h"
#include "../engine/animation/strips/SpriteSheetStrip.h"
#include "../engine/animation/strips/TextStrip.h"


static std::string _prepNum(const char* pat, int digits, int num) {
    std::string s = std::to_string(num);
    int fillDigits = digits - s.length();
    if (fillDigits > 0)
        s = std::string(fillDigits, ' ') + s;

    return s;
}

void GameOverScreen::onStart(olc::PixelGameEngine* pge) { 
    scoreLocation = { 117, 5 };
    Assets::record->playRange(0, 10, true);
    Assets::record->changeTint(olc::RED);

// Setup Score moving from top to center
    auto lerp = new RGNDS::Animation::Strips::LerpStrip<olc::vf2d>(&scoreLocation);
    lerp->changeTarget(
        olc::vf2d{ 64, 88 } + Global::layout->screen_offset, 
        1.5f
    );
    timeline.addStrip(lerp, 0.0f, 0);

// Setup Score Record display
    if (Global::recordScore < Global::score) {
        auto scoreRecordStrip = new RGNDS::Animation::Strips::SpriteSheetStrip(Assets::record, true);
        scoreRecordStrip->transform.pos = olc::vf2d{ 210, 90 } + Global::layout->screen_offset;

        timeline.addStrip(scoreRecordStrip, 1.7f, 0);
    }

// Setup Level display
    auto levelStrip = new RGNDS::Animation::Strips::TextStrip(
        new std::string("Level reached: " + _prepNum("% 3d", 4, Global::level))
    );
    levelStrip->transform.pos = Global::layout->screen_offset + olc::vf2d{ 52, 116 };
    timeline.addStrip(levelStrip, 2.2f, 0);
   
// Setup level record display
    if (Global::recordLevel < Global::level) {
        auto levelRecordStrip = new RGNDS::Animation::Strips::SpriteSheetStrip(Assets::record, true);
        levelRecordStrip->transform.pos = olc::vf2d{ 210, 114 } + Global::layout->screen_offset;

        timeline.addStrip(levelRecordStrip, 2.2f, 0);
    }

#ifdef DEBUG_BUILD 
	auto overlay = new UI::DebugOverlay();
	overlay->addItem("RecordScore", UI::DebugOverlay::TYPE_INT, &Global::recordScore);
	overlay->addItem("RecordLevel", UI::DebugOverlay::TYPE_INT, &Global::recordLevel);
	Global::world->addGameObject(overlay);
#endif

}

void GameOverScreen::onEnd() {
    // Update records
    Global::recordLevel = std::max(Global::recordLevel, Global::level);
    Global::recordScore = std::max(Global::recordScore, Global::score);
    Global::score = 0;
    Global::level = 0;

    Global::world->removeWithAttribute(GameObject::DEBUG);
    
    switchBGMusic(Assets::bgmMenu);
}

bool GameOverScreen::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {
    if (Global::input->released & KEYPAD_A)
        return false;

    Assets::record->onUpdate(deltaTime);
    timeline.onUpdate(deltaTime);
    return true;
}

void GameOverScreen::onDraw(olc::PixelGameEngine* pge) {
    pge->DrawStringDecal(scoreLocation, 
        _prepNum("% 8d", 9, Global::score),
		olc::Pixel{32, 32, 196}
        , { 2.0f, 2.0f }
	);

    timeline.onDraw(pge);

    pge->DrawStringDecal(olc::vf2d{ 40, 296} + Global::layout->screen_offset, "  Press P  ", olc::WHITE, {2.0f, 2.0f});
    pge->DrawStringDecal(olc::vf2d{ 82, 312} + Global::layout->screen_offset, "to continue", olc::WHITE, {1.0f, 1.0f});
}

Scene* GameOverScreen::nextScene() { return new TitleScreen(); }
