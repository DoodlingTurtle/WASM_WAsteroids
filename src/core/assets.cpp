#include <SDL/SDL_mixer.h>
#include "./assets.h"

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

#undef REGISTER_ASSET
#define REGISTER_ASSET(p, c, f, l, t) c* Assets::p = nullptr;
#include "../assets_list.hpp"

Assets::Asset Assets::loaderList[] = {
    #undef REGISTER_ASSET
    #define REGISTER_ASSET(p, c, f, l, t) { Assets::t, f, { .l=&Assets::p } },
    #include "../assets_list.hpp"
};

static auto _count_assets = []() {
    int i = 0;
        #undef REGISTER_ASSET
        #define REGISTER_ASSET(p, c, f, l, t) i++;
        #include "../assets_list.hpp"
    return i;
};


int Assets::numberOfAssets = _count_assets();
int Assets::loadedAssetIndex = 0;
bool Assets::loadFailed = false;

bool Assets::init(std::string* nextFile) {
    if(numberOfAssets == 0) {
    }
    if(loadedAssetIndex == numberOfAssets) return true;
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
                delete *loaderList[a].i.r; break;

            case Assets::SFX:
                Mix_FreeChunk(*loaderList[a].i.c); break;

            case Assets::BGM:
                Mix_FreeMusic(*loaderList[a].i.m); break;
        }
    }
    
    loadedAssetIndex = 0;
};
