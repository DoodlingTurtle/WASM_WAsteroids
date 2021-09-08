#ifndef REGISTER_GO_ATTR
#define REGISTER_GO_ATTR(a) /* to keep the diagnostics happy */
#endif

/* GameObject Types */
REGISTER_GO_ATTR(PLAYER_SHIP)
REGISTER_GO_ATTR(ASTEROID)
REGISTER_GO_ATTR(BULLET)
REGISTER_GO_ATTR(SAUCER)

REGISTER_GO_ATTR(DEBUG)

/* DEAD GOs are removed and deleted from the Main-Loop */
REGISTER_GO_ATTR(DEAD)

/* As long as one of these stays in the world, the maingame will keep running */
REGISTER_GO_ATTR(MAINGAME_COMPONENT)

#undef REGISTER_GO_ATTR