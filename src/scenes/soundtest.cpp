#include "soundtest.h"
#include "../global.h"

#define CNT_SNDS 7
SoundTest::Sound SoundTest::sounds[CNT_SNDS] = {
   {SoundTest::TYPE_SFX, "Ship fire"     , "assets/sfx/sci-fi_sounds/laserSmall_002.ogg"},
   {SoundTest::TYPE_SFX, "Ship explosion", "assets/sfx/sci-fi_sounds/explosionCrunch_004.ogg"},
   {SoundTest::TYPE_SFX, "Ship thrust"   , "assets/sfx/cc0_nocredit/loop_ambient_01.ogg"},
   {SoundTest::TYPE_SFX, "asteroid hit 1", "assets/sfx/cc0_nocredit/explosion_01.ogg"},
   {SoundTest::TYPE_SFX, "asteroid hit 2", "assets/sfx/cc0_nocredit/explosion_02.ogg"},
   {SoundTest::TYPE_BGM, "menu bgm"      , "assets/music/james_gargette/kuia.mp3"},
   {SoundTest::TYPE_BGM, "game bgm"      , "assets/music/james_gargette/oioioioioioi.mp3"}
};

SoundTest::SoundTest()
:playing(-1) { }
SoundTest::~SoundTest() {};

SoundTest::SDL_Sound SoundTest::Sound::load() {
    SDL_Sound r;
    r.m = nullptr;
    switch(t) {
        case SoundTest::TYPE_SFX: 
            r.c = Mix_LoadWAV(file.c_str()); break;

        case SoundTest::TYPE_BGM: 
            r.m = Mix_LoadMUS(file.c_str()); break;
    }

    return r;
}

void SoundTest::Sound::unload(SDL_Sound r) {
    switch(t) {
        case SoundTest::TYPE_SFX: 
            Mix_FreeChunk(r.c); break;

        case SoundTest::TYPE_BGM: 
            Mix_FreeMusic(r.m); break;
    }
}

void SoundTest::Sound::play(SDL_Sound r) {
    switch(t) {
        case SoundTest::TYPE_SFX: 
            Mix_PlayChannel(-1, r.c, 0); break;

        case SoundTest::TYPE_BGM: 
            Mix_PlayMusic(r.m, 0); break;
    }
}

void SoundTest::onStart() {
    for(int a = 0; a < CNT_SNDS; a++) {
        list.push_back(sounds[a].load());
        menu.addOption(sounds[a].label);
    }
}
void SoundTest::onEnd() {
    if(playing > -1) {
        Mix_HaltMusic();
        Mix_HaltChannel(-1);        
        playing = -1;
    }

    for(int a = 0; a < CNT_SNDS; a++) {
        sounds[a].unload(list.at(a));
    }

    menu.clearOptions();
    list.clear();
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
        sounds[p].play(list.at(p));
    }
    menu.selected();
}

void SoundTest::onDraw(olc::PixelGameEngine* pge) { menu.draw(pge); }
