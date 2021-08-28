#pragma once

#include <SDL/SDL_mixer.h>
#include "./olcPixelGameEngine.h"
#include "./Engine.h"

#define __HPP_HEADERS__
#include "./misc/global.hpp"
#include "../global.hpp"
#undef  __HPP_HEADERS__

namespace RGNDS {

    class Global {
    public:

#define REGISTER_GLOBAL(t, e, v) inline static t e = v;
#include "./misc/global.hpp"
#include "../global.hpp"

    };
}
