#ifdef __HPP_HEADERS__

#include "../Input.h"
#include "../world/World.h"

#else

#ifndef REGISTER_GLOBAL
#define REGISTER_GLOBAL(type, name, defaultValue) /* to keep the diagnostics happy */
#endif

REGISTER_GLOBAL(Input         , input       , Input(&Global::game) )
REGISTER_GLOBAL(GameWorld     , world       , GameWorld()          )

#endif
