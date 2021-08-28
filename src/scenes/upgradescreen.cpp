#include <functional>
#include <stdio.h>

#include "./upgradescreen.h"

#include "../engine/olcPixelGameEngine.h"
#include "../engine/Global.h"
#include "../engine/Assets.h"

#include "../gameobjects/ship/shipupgrade_shieldgenerator.h"

#include "./maingame.h"

using namespace RGNDS;

#define ERROR_PRICE_TO_HIGH "You don't have enough points"

#define NUM_TOTAL_UPGRADES 4

static int costs[NUM_TOTAL_UPGRADES] = {
       0,
    1000, 
    2050, 
    3500 
};

static const char* labels[NUM_TOTAL_UPGRADES] = {
    "none",
    "+1 Shield use",
    "Generator capacity up",
    "Generator speed + 50%"
};

static const char* files[NUM_TOTAL_UPGRADES] = {
    "upgrades/none.txt",
    "upgrades/shield.txt",
    "upgrades/gencap.txt",
    "upgrades/genreg.txt"
};


/*=============================================================================
 * UpgradeScreen
 *===========================================================================*/
UpgradeScreen::UpgradeScreen( MainGameScreen* backscene ) : Scene() , backscene(backscene)
{
    selection.transform.pos.y += 200;
    selection.transform.pos.x += 8;

    descriptionlocation.x += 8;
    descriptionlocation.y += 34;

    scorelocation.x += 8.0f;
    scorelocation.y += 8.0f;

    costlocation.x += 8;
    costlocation.y = 180;
}
UpgradeScreen::~UpgradeScreen(){}


void UpgradeScreen::onStart(olc::PixelGameEngine* pge){
    // Shield is always available    
    upgrade_data.push_back(1);

// Randomize the other upgrades        
// TODO: (DoTu) add more upgrade options
    int rnd = 2 + (RandF()*2.0f);
    upgrade_data.push_back(rnd);

// Append the None Option
    upgrade_data.push_back(0);

    auto _readDescription = [this](const char* filename) {
        std::string str;

        FILE* f = fopen(filename, "rb");
        if(f) {
            while(!feof(f)) {
                char buffer[1024] { 0 };
                fgets(buffer, 1024, f);
                
                str += std::string(buffer);
            }

            fclose(f);
        }

        return str;
    };

    for(auto u : upgrade_data) {
        selection.addOption(labels[u]);
        description.push_back(Assets::loadText(files[u]));
    }

    showError = false;

}

void UpgradeScreen::onEnd() {
    upgrade_data.clear();
    description.clear();
    selection.clearOptions();
}

bool UpgradeScreen::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {

    if(Global::input->pressed&KEYPAD_DOWN)
        selection.selectNext();
    else if(Global::input->pressed&KEYPAD_UP)
        selection.selectPrev();
    else if(Global::input->pressed&(KEYPAD_A|KEYPAD_START))
    {
        int selected = upgrade_data.at(selection.selected());
        int cost = costs[selected] * (backscene->game_difficulty);

        if(Global::score >= cost) {
            Global::score -= cost;

            switch(selected) {
                
                case 0: // none 
                    break;

                case 1: // shielduses 
                    Global::shipStats->registerNewComponent( new ShipUpgrade_ShieldGenerator() );
                    break;

                case 2: // Generator capacity 
                    Global::shipStats->generatorcapacity += 15;
                    break;

                case 3: // Generator regen
                    Global::shipStats->generatorrecovery *= 1.5f;
                    break;

            }
            return false;
        }
        else {
            showError = true;    
        }
    }

    return true;
}


static void _printPGE(
    olc::PixelGameEngine* pge, 
    const olc::vf2d pos, 
    const char* buffer,
    olc::Pixel pixel,
    olc::vf2d scale={1.0f, 1.0f}
) {
    std::string s(buffer);
    pge->DrawStringDecal(
            pos, s, 
            pixel,
            scale
    );
}

void UpgradeScreen::onDraw(olc::PixelGameEngine* pge) {
    
    pge->FillRect(
        22, 199 + (10 *selection.selected()),
        288 , 10,
        pix_menubg
    );
    selection.draw(pge);

    if(showError)
        _printPGE(pge, { 16, 116 }, ERROR_PRICE_TO_HIGH, olc::RED);

    char buffer[17]{ 0 };
    std::sprintf(buffer, "Score: % 8d", Global::score);
    _printPGE(pge, scorelocation, buffer,olc::Pixel(0, 80, 255), { 2.0f, 2.0f });

    pge->DrawStringDecal(
            descriptionlocation, 
            description[selection.selected()], 
            olc::WHITE
    );

    char str[32];
    std::sprintf(
            str,
            "cost: % 24d", 
            (int)(costs[upgrade_data.at(selection.selected())] * (backscene->game_difficulty))
    );
    _printPGE(pge, costlocation, str, olc::WHITE);
   
}

Scene* UpgradeScreen::nextScene() { return backscene; }

