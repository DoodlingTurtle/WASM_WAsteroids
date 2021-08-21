#ifndef _ASSETS_H_
#define _ASSETS_H_

#include <iostream>
#include <SDL/SDL_mixer.h>
#include "./olcPixelGameEngine.h"

class Assets {
public:
    enum Type { SPRITE, SFX, BGM };

    union AssetItem {
        olc::Renderable** r;
        Mix_Chunk**       c;
        Mix_Music**       m;
    };

    struct Asset {
        Type t;
        std::string file;
        AssetItem i;
    };

    static Asset loaderList[];
    
    static std::string loadText(std::string fileName);

#define REGISTER_ASSET(p, c, f, l, t) static c* p;
#include "../assets_list.hpp"

    /* starts to load all assets */
    static bool init(std::string* nextLoadedFile);
    static void deinit();

protected:
    static int loadedAssetIndex;
    static bool loadFailed;
    static int numberOfAssets;
};


#endif
