#ifdef __HPP_HEADERS__

#include "../Input.h"
#include "../world/World.h"

#else

#ifndef REGISTER_GLOBAL
#define REGISTER_GLOBAL(type, name, defaultValue) /* to keep the diagnostics happy */
#endif

REGISTER_GLOBAL(Game*         , game        , nullptr)
REGISTER_GLOBAL(Input*        , input       , nullptr)
REGISTER_GLOBAL(GameWorld*    , world       , nullptr)

#endif
