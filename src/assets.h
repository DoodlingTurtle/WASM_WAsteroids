#ifndef _ASSETS_H_
#define _ASSETS_H_

#include "olcPixelGameEngine.h"
#include <SDL/SDL_mixer.h>
#include <iostream>

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

    static Mix_Music*       bgmMenu;
    static Mix_Music*       bgmGame;

    static olc::Renderable* ship;
    static Mix_Chunk*       shipThrust;
    static Mix_Chunk*       shipExplode;
    
    static olc::Renderable* shields;
    static Mix_Chunk*       shieldBump;

    static olc::Renderable* bullets;
    static Mix_Chunk*       bullet_fire_1;

    static Mix_Chunk*       asteroid_hit_1;
    static Mix_Chunk*       asteroid_hit_2;


    /* starts to load all assets */
    static bool init(std::string* nextLoadedFile);
    static void deinit();

protected:
    static int loadedAssetIndex;
    static bool loadFailed;
};


#endif
