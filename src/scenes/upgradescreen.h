#ifndef __UpgradeScreen__
#define __UpgradeScreen__

#include <string>

#include "scene.h"
#include "gameobjects/ship/shipstats.h"
#include "textmenu.h"
#include "transform.h"

class UpgradeScreen : public Scene {
public:
    UpgradeScreen(
            ShipStats*, int* score, float* game_difficulty);
    virtual ~UpgradeScreen();

    void onDraw(olc::PixelGameEngine*) override;
    void onUpdate(olc::PixelGameEngine*, float) override;

protected:
    void onStart() override;
    void onEnd() override;
    
private:
    ShipStats* shipstats;
    int*       score;
    TextMenu   selection;

    std::vector<std::string> description;
    olc::vf2d descriptionlocation;
    olc::vf2d scorelocation;
    olc::vf2d costlocation;

    bool showError;

    std::vector<int> upgrade_data;
    std::function<void()> handlers[4];

    float* game_difficulty;

};

#endif
