#ifdef __HPP_HEADER__ /** Put all your includes for the component classes here */
#include "./gamecomponents.h"
#else

#ifndef REGISTER_GO_COMPONENT
#define REGISTER_GO_COMPONENT(className) /* to keep the diagnostics happy */
#endif

REGISTER_GO_COMPONENT(ShipShieldDeflectable)
REGISTER_GO_COMPONENT(PlayerKiller)
REGISTER_GO_COMPONENT(PlayerHitable)
REGISTER_GO_COMPONENT(EnemyHitable)

#undef REGISTER_GO_COMPONENT

#endif
