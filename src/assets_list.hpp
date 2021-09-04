/**
 *  propertyname ( example bgMenu will becomes Assets::bgmMenu )
 *
 * Pointer Type: Mix_Music, Mix_Chunk, olc::Renderable, RGNDS::SpriteSheet
 *
 * asset filepath
 *
 * letter based on Pointer type:  Mix_Music = m,  
 *                                Mix_Chunk = c, 
 *                                olc::Renderable = r,
 *                                RGNDS::SpriteSheet = sh
 *
 * value based on Pointer type:  Mix_Music = BGM,  
 *                               Mix_Chunk = SFX, 
 *                               olc::Renderable = SPRITE,
 *                               RGNDS::SpriteSheet = sh 
 */

#ifndef REGISTER_ASSET
#define REGISTER_ASSET(a, b, c, d, e) /* too keep the diagnostics happy */
#endif

REGISTER_ASSET(bgmMenu        ,Mix_Music          ,"./assets/music/james_gargette/kuia.oga"             ,m  ,BGM         )
											        
REGISTER_ASSET(ship           ,olc::Renderable    ,"./assets/sprites/ship.png",                          r  ,SPRITE      )
REGISTER_ASSET(shipThrust     ,Mix_Chunk          ,"./assets/sfx/cc0_nocredit/loop_ambient_01.ogg"      ,c  ,SFX         )
REGISTER_ASSET(shipExplode    ,Mix_Chunk          ,"./assets/sfx/sci-fi_sounds/explosionCrunch_004.ogg" ,c  ,SFX         )
											        
REGISTER_ASSET(shields        ,olc::Renderable    ,"./assets/sprites/shield.png"                        ,r  ,SPRITE      )
REGISTER_ASSET(shieldBump     ,Mix_Chunk          ,"./assets/sfx/sci-fi_sounds/laserLarge_002.ogg"      ,c  ,SFX         )
											        
REGISTER_ASSET(bullets        ,olc::Renderable    ,"./assets/sprites/shot.png"                          ,r  ,SPRITE      )
REGISTER_ASSET(laser1         ,Mix_Chunk          ,"./assets/sfx/bfxr_sounds/Laser1.oga"                ,c  ,SFX         )
REGISTER_ASSET(laser2         ,Mix_Chunk          ,"./assets/sfx/bfxr_sounds/Laser2.oga"                ,c  ,SFX         )
											        
REGISTER_ASSET(asteroid_hit_1 ,Mix_Chunk          ,"./assets/sfx/cc0_nocredit/explosion_01.ogg"         ,c  ,SFX         )
REGISTER_ASSET(asteroid_hit_2 ,Mix_Chunk          ,"./assets/sfx/cc0_nocredit/explosion_02.ogg"         ,c  ,SFX         )

REGISTER_ASSET(record         ,RGNDS::SpriteSheet ,"./assets/sprites/record.png"                        ,sh ,SPRITESHEET )

REGISTER_ASSET(bgmLV01        ,Mix_Music          ,"./assets/music/james_gargette/lv01.oga"             ,m  ,BGM         )
REGISTER_ASSET(bgmLV02        ,Mix_Music          ,"./assets/music/james_gargette/lv02.oga"             ,m  ,BGM         )
REGISTER_ASSET(bgmLV03        ,Mix_Music          ,"./assets/music/james_gargette/lv03.oga"             ,m  ,BGM         )
REGISTER_ASSET(bgmLV04        ,Mix_Music          ,"./assets/music/james_gargette/lv04.oga"             ,m  ,BGM         )
REGISTER_ASSET(bgmLV05        ,Mix_Music          ,"./assets/music/james_gargette/lv05.oga"             ,m  ,BGM         )

#undef REGISTER_ASSETREGISTER_ASSET