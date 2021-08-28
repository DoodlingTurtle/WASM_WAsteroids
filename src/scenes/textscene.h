#pragma once

#include <string>

#include "../engine/olcPixelGameEngine.h"
#include "../engine/Scene.h"

using namespace RGNDS;

class TextScene: public Scene {
public:
    TextScene(std::string assetFileName);
    ~TextScene();

    void onDraw(olc::PixelGameEngine*) override;
    bool onUpdate(olc::PixelGameEngine*, float) override;

    Scene* nextScene() override;

protected:
    void onStart(olc::PixelGameEngine*) override;
    void onEnd() override;


private:
    olc::vf2d   text_position;
    std::string text;
    std::string fileName;
    
    std::string help_text;
    olc::vf2d   help_position;
};
