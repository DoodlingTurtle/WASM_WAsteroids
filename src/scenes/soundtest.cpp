#include "./soundtest.h"
#include "global.h"

#define CNT_SNDS 7
SoundTest::Sound SoundTest::sounds[CNT_SNDS] = {
   {SoundTest::TYPE_SFX, "Ship fire"     , { .c=&Assets::bullet_fire_1  }},
   {SoundTest::TYPE_SFX, "Ship explosion", { .c=&Assets::shipExplode    }},
   {SoundTest::TYPE_SFX, "Ship thrust"   , { .c=&Assets::shipThrust     }},

   {SoundTest::TYPE_SFX, "asteroid hit 1", { .c=&Assets::asteroid_hit_1 }},
   {SoundTest::TYPE_SFX, "asteroid hit 2", { .c=&Assets::asteroid_hit_2 }},

   {SoundTest::TYPE_BGM, "menu bgm"      , { .m=&Assets::bgmMenu        }},
   {SoundTest::TYPE_BGM, "game bgm"      , { .m=&Assets::bgmGame        }}
};

void SoundTest::Sound::play() {
    switch(t) {
        case SoundTest::TYPE_SFX: 
            Mix_PlayChannel(-1, *r.c, 0); break;

        case SoundTest::TYPE_BGM: 
            Mix_PlayMusic(*r.m, 0); break;
    }
}

void SoundTest::onStart() {
    for(int a = 0; a < CNT_SNDS; a++)
        menu.addOption(sounds[a].label);
}
void SoundTest::onEnd() {
    Mix_HaltMusic();
    Mix_HaltChannel(-1);        

    menu.clearOptions();
}

void SoundTest::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {
    if(Global::gameInput->pressed&KEYPAD_DOWN)
        menu.selectNext();
        
    if(Global::gameInput->pressed&KEYPAD_UP)
        menu.selectPrev();

    if(Global::gameInput->pressed&KEYPAD_A) {
        Mix_HaltMusic();
        Mix_HaltChannel(-1);
        int p = menu.selected();
        sounds[p].play();
    }
    menu.selected();
}

void SoundTest::onDraw(olc::PixelGameEngine* pge) { menu.draw(pge); }
