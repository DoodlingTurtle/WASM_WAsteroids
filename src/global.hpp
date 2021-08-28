#ifdef __HPP_HEADERS__

    #include <SDL/SDL_mixer.h>
    
    #include "./engine/olcPixelGameEngine.h"

    #include "./gameobjects/ship/shipstats.h"
    
    #include "./particles.h"
    #include "./config.h"

#else

#ifndef REGISTER_GLOBAL
#define REGISTER_GLOBAL(type, name, defaultValue) /* to keep the diagnostics happy */
#endif

REGISTER_GLOBAL(olc::PixelGameEngine*, pge         , nullptr     )
REGISTER_GLOBAL(ShipStats            , shipStats   , ShipStats() )
REGISTER_GLOBAL(ScreenLayout*        , layout      , &screenLayouts[0])
REGISTER_GLOBAL(Mix_Music*           , bgMusic     , nullptr     )
REGISTER_GLOBAL(int                  , score       , 0           )
REGISTER_GLOBAL(int                  , recordScore , 0           )
REGISTER_GLOBAL(int                  , level       , 0           )
REGISTER_GLOBAL(int                  , recordLevel , 0           )

#undef REGISTER_GLOBAL
#endif
