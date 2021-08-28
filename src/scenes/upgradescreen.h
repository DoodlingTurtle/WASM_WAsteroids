#pragma once

#include <string>

#include "../engine/Transform.h"
#include "../engine/ui/Textmenu.h"
#include "../engine/Scene.h"

#include "../gameobjects/ship/shipstats.h"

using namespace RGNDS;

class UpgradeScreen : public Scene {
public:
    UpgradeScreen( ShipStats*, int* score, float* game_difficulty );
    virtual ~UpgradeScreen();

    void onDraw(olc::PixelGameEngine*) override;
    bool onUpdate(olc::PixelGameEngine*, float) override;

    Scene* nextScene() override;

protected:
    void onStart() override;
    void onEnd() override;
    
private:
    ShipStats* shipstats;
    int*       score;
    UI::TextMenu selection;

    std::vector<std::string> description;
    olc::vf2d descriptionlocation;
    olc::vf2d scorelocation;
    olc::vf2d costlocation;

    bool showError;

    std::vector<int> upgrade_data;
    std::function<void()> handlers[4];

    float* game_difficulty;

};
