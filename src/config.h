#ifndef __MainConfig_H__
#define __MainConfig_H__

#include "olcPixelGameEngine.h"

#define APP_SCREEN_WIDTH 256
#define APP_SCREEN_HEIGHT 384
#define APP_SCREEN_SCALE 1

#define MAX_ASTEROIDS 32 
#define CNT_STARS 64
#define MAX_SHOT_CNT 32

#ifndef PI
#define PI 3.141592653589793238462643383279
#endif // PI

#ifndef PI2
#define PI2 6.283185307179586476925286766558
#endif // PI2

#define RandF() ((float)rand() / (float)RAND_MAX)

#ifdef DEBUG_BUILD
#include <iostream>
#define Debug(msg) std::cout << msg << std::endl
#else
#define Debug(msg) /**/
#endif

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

    olc::vf2d titleScreen_title_placement,
              titleScreen_menu_placement;
    
    olc::vf2d help_position;
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

#endif

