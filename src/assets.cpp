#include "assets.h"
#include <SDL/SDL_mixer.h>


std::string Assets::loadText(std::string fileName) {
    std::string str;
    str = "assets/" + fileName;

    FILE* f = fopen(str.c_str(), "rb");
    if(f) {
        str = "";
        while(!feof(f)) {
            char buffer[1024] { 0 };
            fgets(buffer, 1024, f);
            
            str += std::string(buffer);
        }

        fclose(f);
    }

    return str;
}

olc::Renderable* Assets::ship           = nullptr; 
olc::Renderable* Assets::shields        = nullptr;
olc::Renderable* Assets::bullets        = nullptr; 
Mix_Chunk*       Assets::shipThrust     = nullptr;
Mix_Chunk*       Assets::shipExplode    = nullptr; 
Mix_Chunk*       Assets::shieldBump     = nullptr;
Mix_Chunk*       Assets::asteroid_hit_1 = nullptr;
Mix_Chunk*       Assets::asteroid_hit_2 = nullptr;
Mix_Music*       Assets::bgmMenu        = nullptr; 
Mix_Music*       Assets::bgmGame        = nullptr;

#define CNT_ASSETS 11 
Assets::Asset Assets::loaderList[CNT_ASSETS] = {
    { Assets::SPRITE, "assets/sprites/ship.png",                          { .r=&Assets::ship           }},
    { Assets::SFX,    "assets/sfx/cc0_nocredit/loop_ambient_01.ogg",      { .c=&Assets::shipThrust     }},
    { Assets::SFX,    "assets/sfx/sci-fi_sounds/explosionCrunch_004.ogg", { .c=&Assets::shipExplode    }},

    { Assets::SPRITE, "assets/sprites/shield.png",                        { .r=&Assets::shields        }},
    { Assets::SFX,    "assets/sfx/sci-fi_sounds/laserLarge_002.ogg",      { .c=&Assets::shieldBump     }},

    { Assets::SPRITE, "assets/sprites/shot.png",                          { .r=&Assets::bullets        }},
    { Assets::SFX,    "assets/sfx/sci-fi_sounds/laserSmall_002.ogg",      { .c=&Assets::bullet_fire_1  }},

    { Assets::SFX,    "assets/sfx/cc0_nocredit/explosion_01.ogg",         { .c=&Assets::asteroid_hit_1 }},
    { Assets::SFX,    "assets/sfx/cc0_nocredit/explosion_02.ogg",         { .c=&Assets::asteroid_hit_2 }},

    { Assets::BGM,    "assets/music/james_gargette/kuia.mp3",             { .m=&Assets::bgmMenu        }},
    { Assets::BGM,    "assets/music/james_gargette/oioioioioioi.mp3",     { .m=&Assets::bgmGame        }}
};

int Assets::loadedAssetIndex = 0;
bool Assets::loadFailed = false;

bool Assets::init(std::string* nextFile) {
    if(loadedAssetIndex == CNT_ASSETS) return true;
    if(loadFailed) {
        *nextFile = loaderList[loadedAssetIndex].file;
        return false;
    }
    
    switch(loaderList[loadedAssetIndex].t) {
        case Assets::SPRITE:
            *loaderList[loadedAssetIndex].i.r = new olc::Renderable();
            if(olc::OK != ((*loaderList[loadedAssetIndex].i.r)->Load(loaderList[loadedAssetIndex].file))) {
                loadFailed = true; 
                return false;
            } break;

        case Assets::SFX:
            *loaderList[loadedAssetIndex].i.c = Mix_LoadWAV(loaderList[loadedAssetIndex].file.c_str());
            if(!(*loaderList[loadedAssetIndex].i.c)) {
                loadFailed = true;
                return false;
            } break;

        case Assets::BGM:
            *loaderList[loadedAssetIndex].i.m = Mix_LoadMUS(loaderList[loadedAssetIndex].file.c_str());
            if(!(*loaderList[loadedAssetIndex].i.m)) {
                loadFailed = true;
                return false;
            } break;
    }


    loadedAssetIndex++;
    return false;
}


void Assets::deinit() {
    
    for(int a = 0; a < loadedAssetIndex; a++) {
        switch(loaderList[a].t) {
            case Assets::SPRITE:
                delete loaderList[a].i.r; break;

            case Assets::SFX:
                Mix_FreeChunk(*loaderList[a].i.c); break;

            case Assets::BGM:
                Mix_FreeMusic(*loaderList[a].i.m); break;
        }
    }
    
    loadedAssetIndex = 0;
};
