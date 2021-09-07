#pragma once

#include <string>

#include "../engine/Transform.h"
#include "../engine/ui/TextMenu.h"
#include "../engine/Scene.h"

#include "../gameobjects/ship/shipstats.h"

using namespace RGNDS;

class MainGameScreen;


class UpgradeScreen : public Scene {
public:
    static void resetPool();

    UpgradeScreen(MainGameScreen* backscene);
    virtual ~UpgradeScreen();

    void onDraw(olc::PixelGameEngine*) override;
    bool onUpdate(olc::PixelGameEngine*, float) override;

    Scene* nextScene() override;

protected:
    void onStart(olc::PixelGameEngine*) override;
    void onEnd() override;
    
private:
	struct UpgradeSlot {
		int grp, grpIndex, listIndex;
	};

    static std::vector<std::vector<int>> upgrade_pool;

    MainGameScreen*          backscene;
    UI::TextMenu             selection;
    std::vector<std::string> description;
    olc::vf2d                descriptionlocation;
    olc::vf2d                scorelocation;
    olc::vf2d                costlocation;

    bool showError;

    std::vector<int>         upgrade_data;
    std::vector<UpgradeSlot> upgrade_slotdata;
};
