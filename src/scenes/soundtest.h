#ifndef __SOUNDTEST_H__
#define __SOUNDTEST_H__

#include "../olcPixelGameEngine.h"
#include "../scene.h"

#include "../textmenu.h"

#include <SDL/SDL_mixer.h>
#include <vector>

class SoundTest: public Scene {
public:

    enum SOUNDTYPE {
        TYPE_SFX,
        TYPE_BGM
    };

    union SDL_Sound {
        Mix_Chunk* c;
        Mix_Music* m;
    };

    struct Sound {
        SOUNDTYPE t;
        std::string label, file;
        
        SDL_Sound load();
        void unload(SDL_Sound s);
        void play(SDL_Sound s);
    };

    static Sound sounds[];

    SoundTest();
    ~SoundTest();

    void onDraw(olc::PixelGameEngine*) override;
    void onUpdate(olc::PixelGameEngine*, float) override;

protected:
    void onStart() override;
    void onEnd() override;

private:
    int playing;
    std::vector<SDL_Sound> list;
    TextMenu menu;
};
#endif