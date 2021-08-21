#ifndef __Global_H__
#define __Global_H__


#include <SDL/SDL_mixer.h>
#include "core/olcPixelGameEngine.h"

#define __HPP_HEADERS__
#include "global.hpp"
#undef  __HPP_HEADERS__


class Global {
public:

    #define REGISTER_GLOBAL(t, e, v) static t e;
    #include "../global.hpp"

    static olc::Key gamecontrols[5];
    static void switchBGMusic(Mix_Music* asset);


};

#endif
