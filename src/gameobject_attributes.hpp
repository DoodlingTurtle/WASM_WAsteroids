#ifndef REGISTER_GO_ATTR
#define REGISTER_GO_ATTR(a) /* - to keep the diagnostics happy */
#endif

/* GameObject Types */
REGISTER_GO_ATTR(PLAYER_SHIP)
REGISTER_GO_ATTR(ASTEROID)

/* Collider Groups */
REGISTER_GO_ATTR(SHIP_KILLER)
REGISTER_GO_ATTR(BULLET_COLLIDEABLE)

/* Attention!!!: Only give these two SpaceObj Instances 
   They tell the Main-Loop, what Instances can be drawn or not */
REGISTER_GO_ATTR(SPACE_OBJ_DRAW)
REGISTER_GO_ATTR(SPACE_OBJ_UPDATE)

/* DEAD GOs are removed and deleted from the Mail-Loop */
REGISTER_GO_ATTR(DEAD)

/* As long as one of these stays in the world, the maingame will keep running */
REGISTER_GO_ATTR(MAINGAME_COMPONENT)

#undef REGISTER_GO_ATTR
