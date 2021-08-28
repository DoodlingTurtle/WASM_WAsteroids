#pragma once

#include <vector>
#include <SDL/SDL_mixer.h>

#include "../engine/olcPixelGameEngine.h"
#include "../engine/Assets.h"
#include "../engine/ui/TextMenu.h"
#include "../engine/Scene.h"

using namespace RGNDS;

class SoundTest: public Scene {
public:

    enum SOUNDTYPE {
        TYPE_SFX,
        TYPE_BGM
    };

    union SDL_Sound {
        Mix_Chunk** c;
        Mix_Music** m;
    };

    struct Sound {
        SOUNDTYPE t;
        std::string label;
        SDL_Sound r; 
        
        void play();
    };

    static Sound sounds[];

    void onDraw(olc::PixelGameEngine*) override;
    bool onUpdate(olc::PixelGameEngine*, float) override;

    Scene* nextScene() override;

protected:
    void onStart(olc::PixelGameEngine*) override;
    void onEnd() override;

private:
    UI::TextMenu menu;
};
