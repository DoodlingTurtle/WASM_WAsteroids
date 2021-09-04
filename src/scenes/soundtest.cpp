#include "./soundtest.h"
#include "../engine/Global.h"
using namespace RGNDS;

#define CNT_SNDS 12 
SoundTest::Sound SoundTest::sounds[CNT_SNDS] = {
   {SOUNDTYPE::TYPE_SFX, "Ship fire 1"   , { .c=&Assets::laser1         }},
   {SOUNDTYPE::TYPE_SFX, "Ship fire 2"   , { .c=&Assets::laser2         }},
   {SOUNDTYPE::TYPE_SFX, "Ship explosion", { .c=&Assets::shipExplode    }},
   {SOUNDTYPE::TYPE_SFX, "Ship thrust"   , { .c=&Assets::shipThrust     }},

   {SOUNDTYPE::TYPE_SFX, "asteroid hit 1", { .c=&Assets::asteroid_hit_1 }},
   {SOUNDTYPE::TYPE_SFX, "asteroid hit 2", { .c=&Assets::asteroid_hit_2 }},

   {SOUNDTYPE::TYPE_BGM, "menu bgm"      , { .m=&Assets::bgmMenu        }},
   {SOUNDTYPE::TYPE_BGM, "lv1 bgm"       , { .m=&Assets::bgmLV01        }},
   {SOUNDTYPE::TYPE_BGM, "lv2 bgm"       , { .m=&Assets::bgmLV02        }},
   {SOUNDTYPE::TYPE_BGM, "lv3 bgm"       , { .m=&Assets::bgmLV03        }},
   {SOUNDTYPE::TYPE_BGM, "lv4 bgm"       , { .m=&Assets::bgmLV04        }},
   {SOUNDTYPE::TYPE_BGM, "lv5 bgm"       , { .m=&Assets::bgmLV05        }}
};

void SoundTest::Sound::play() {
    switch(t) {
        case SOUNDTYPE::TYPE_SFX: 
            Mix_PlayChannel(-1, *r.c, 0); break;

        case SOUNDTYPE::TYPE_BGM: 
            Mix_PlayMusic(*r.m, 0); break;
    }
}

void SoundTest::onStart(olc::PixelGameEngine* pge) {
    for(int a = 0; a < CNT_SNDS; a++)
        menu.addOption(sounds[a].label);
}
void SoundTest::onEnd() {
    Mix_HaltMusic();
    Mix_HaltChannel(-1);        

    menu.clearOptions();
}

bool SoundTest::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {
    if(Global::input->pressed&KEYPAD_DOWN)
        menu.selectNext();
        
    if(Global::input->pressed&KEYPAD_UP)
        menu.selectPrev();

    if(Global::input->pressed&KEYPAD_A) {
        Mix_HaltMusic();
        Mix_HaltChannel(-1);
        int p = menu.selected();
        sounds[p].play();
    }
    menu.selected();

    return true;
}

void SoundTest::onDraw(olc::PixelGameEngine* pge) { menu.draw(pge); }

Scene* SoundTest::nextScene() {
    return nullptr;
    //TODO: replace with propper content
}


