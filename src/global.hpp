#ifdef __HPP_HEADERS__

    #include <SDL/SDL_mixer.h>
    
    #include "core/olcPixelGameEngine.h"
    #include "core/gameinput.h"
   
    #include "gameworld.h"
    #include "gameobjects/ship/shipstats.h"
    
    #include "./particles.h"
    #include "./config.h"

    #include "./DebugOverlay.h"

#else

REGISTER_GLOBAL(GameInput*           , gameInput   , nullptr)
REGISTER_GLOBAL(olc::PixelGameEngine*, pge         , nullptr)
REGISTER_GLOBAL(ShipStats*           , shipStats   , nullptr)
REGISTER_GLOBAL(GameWorld*           , world       , nullptr)
REGISTER_GLOBAL(ScreenLayout*        , layout      , nullptr)
REGISTER_GLOBAL(Mix_Music*           , bgMusic     , nullptr)
REGISTER_GLOBAL(int                  , score       , 0      )
REGISTER_GLOBAL(int                  , recordScore , 0      )
REGISTER_GLOBAL(int                  , level       , 0      )
REGISTER_GLOBAL(int                  , recordLevel , 0      )

#endif
