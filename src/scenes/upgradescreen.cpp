#include "upgradescreen.h"
#include <functional>
#include <stdio.h>

#include "../olcPixelGameEngine.h"

#include "../global.h"

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
    "./assets/upgrades/none.txt",
    "./assets/upgrades/shield.txt",
    "./assets/upgrades/gencap.txt",
    "./assets/upgrades/genreg.txt"
};


/*=============================================================================
 * UpgradeScreen
 *===========================================================================*/
UpgradeScreen::UpgradeScreen(
        ShipStats* stats, 
        int* score,
        float* game_difficulty
)
:Scene(), shipstats(stats), score(score), game_difficulty(game_difficulty)
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


void UpgradeScreen::onStart(){
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
                char buffer[1024];
                fgets(buffer, 1024, f);
                
                str += std::string(buffer);
            }

            fclose(f);
        }

        return str;
    };

    for(auto u : upgrade_data) {
        selection.addOption(labels[u]);
        description.push_back(_readDescription(files[u]));
    }

    showError = false;

}

void UpgradeScreen::onEnd() {
    upgrade_data.clear();
    description.clear();
    selection.clearOptions();
}

void UpgradeScreen::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {

    if(Global::gameInput->pressed&KEYPAD_DOWN)
        selection.selectNext();
    else if(Global::gameInput->pressed&KEYPAD_UP)
        selection.selectPrev();
    else if(Global::gameInput->pressed&(KEYPAD_A|KEYPAD_START))
    {
        int selected = upgrade_data.at(selection.selected());
        int cost = costs[selected];

        if(*score >= cost) {
            *score -= cost;

            switch(selected) {
                case 0: // none 
                    break;

                case 1: // shielduses 
                    //TODO: Add ShipUpgrade_ShieldGenerator to Ship_InvokableComponents
                    //shipstats->shielduses += 1;
                    break;

                case 2: // Generator capacity 
                    shipstats->generatorcapacity += 15;
                    break;

                case 3: // Generator regen
                    shipstats->generatorrecovery *= 1.5f;
                    break;

            }
            exit();
        }
        else {
            showError = true;    
        }
    }
}


static void _printPGE(
    olc::PixelGameEngine* pge, 
    const olc::vf2d pos, 
    const char* buffer,
    olc::Pixel pixel
) {
    std::string s(buffer);
    pge->DrawStringDecal(
            pos, s, 
            pixel
    );
}

void UpgradeScreen::onDraw(olc::PixelGameEngine* pge) {
    
    pge->FillRect(
        22, 199 + (10 *selection.selected()),
        288 , 10,
        pix_menubg
    );
    selection.draw(pge);

    if(showError) {
        pge->DrawStringDecal(
            { 308, 24 }, ERROR_PRICE_TO_HIGH, olc::RED);
    }

    char buffer[17]{ 0 };
    std::sprintf(buffer, "Score: % 8d", *score);
    _printPGE(pge, scorelocation, buffer,olc::Pixel(0, 80, 255));

    pge->DrawStringDecal(
            descriptionlocation, 
            description[selection.selected()], 
            olc::WHITE
    );

    char str[32];
    std::sprintf(
            str,
            "cost: % 24d", 
            (int)(costs[upgrade_data.at(selection.selected())] * (*game_difficulty))
    );
    _printPGE(pge, costlocation, str, olc::WHITE);
   
}
