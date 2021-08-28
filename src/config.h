#pragma once 

#include "./engine/olcPixelGameEngine.h"
#include "./engine/Macros.h"
#include <SDL/SDL_mixer.h>

#define APP_SCREEN_WIDTH 256
#define APP_SCREEN_HEIGHT 384
#define APP_SCREEN_SCALE 1

#define MAX_ASTEROIDS 32 
#define CNT_STARS 64
#define MAX_SHOT_CNT 32

/*
enum GameInput {
    GAMEINPUT_ACCELERATE,
    GAMEINPUT_TURNLEFT,
    GAMEINPUT_TURNRIGHT,
    GAMEINPUT_FIRE,
    GAMEINPUT_SHIELD
};
*/

struct ScreenLayout {
    std::string title;
    int app_width, 
        app_height, 
        app_scale;

    olc::vf2d titleScreen_title_placement;
    float titleScreen_title_scale;
    olc::vf2d titleScreen_menu_placement;
    
    olc::vf2d ship_energy_full_pos , ship_energy_full_size
            , ship_energy_empty_pos, ship_energy_empty_size;

    olc::vf2d help_position;

    olc::vf2d screen_offset;
};


extern olc::Key GameKeyMap[11];
extern olc::Pixel pix_menubg;
extern olc::Pixel pix_asteroid;

extern int layer_asteroids;
extern int layer_shots;
extern int layer_stars;
extern int layer_ship;
extern int layer_blackout;
extern int layer_particles;

extern ScreenLayout screenLayouts[];

void switchBGMusic(Mix_Music* asset);
