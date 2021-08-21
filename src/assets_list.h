/**
 *  propertyname ( example bgMenu will becomes Assets::bgmMenu )
 *
 * Pointer Type: Mix_Music, Mix_Chunk, olc::Renderable
 *
 * asset filepath
 *
 * letter based on Pointer type:  Mix_Music = m,  Mix_Chunk = c, olc::Renderable = r
 *
 * value based on Pointer type:  Mix_Music = BGM,  Mix_Chunk = SFX, olc::Renderable = SPRITE 
 */

#ifndef REGISTER_ASSET
#define REGISTER_ASSET(a, b, c, d, e) /* too keep the diagnostics happy */
#endif

REGISTER_ASSET(bgmMenu,        Mix_Music,       "./assets/music/james_gargette/kuia.oga",              m, BGM    )
REGISTER_ASSET(bgmGame,        Mix_Music,       "./assets/music/james_gargette/oioioioioioi.oga",      m, BGM    )
												 
REGISTER_ASSET(ship,           olc::Renderable, "./assets/sprites/ship.png",                           r, SPRITE )
REGISTER_ASSET(shipThrust,     Mix_Chunk,       "./assets/sfx/cc0_nocredit/loop_ambient_01.ogg",       c, SFX    )
REGISTER_ASSET(shipExplode,    Mix_Chunk,       "./assets/sfx/sci-fi_sounds/explosionCrunch_004.ogg",  c, SFX    )
												 
REGISTER_ASSET(shields,        olc::Renderable, "./assets/sprites/shield.png",                         r, SPRITE )
REGISTER_ASSET(shieldBump,     Mix_Chunk,       "./assets/sfx/sci-fi_sounds/laserLarge_002.ogg",       c, SFX    )
												 
REGISTER_ASSET(bullets,        olc::Renderable, "./assets/sprites/shot.png",                           r, SPRITE )
REGISTER_ASSET(bullet_fire_1,  Mix_Chunk,       "./assets/sfx/sci-fi_sounds/laserSmall_002.ogg",       c, SFX    )
												 
REGISTER_ASSET(asteroid_hit_1, Mix_Chunk,       "./assets/sfx/cc0_nocredit/explosion_01.ogg",          c, SFX    )
REGISTER_ASSET(asteroid_hit_2, Mix_Chunk,       "./assets/sfx/cc0_nocredit/explosion_02.ogg",          c, SFX    )

#undef REGISTER_ASSET