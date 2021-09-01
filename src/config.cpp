#include "./config.h"


olc::Pixel pix_menubg = olc::Pixel(22, 36, 134, 200);
olc::Pixel pix_asteroid = olc::Pixel(138, 100, 73, 255);

int layer_asteroids = 0;
int layer_shots = 0;
int layer_stars = 0;
int layer_ship = 0;
int layer_blackout = 0;
int layer_particles = 0;

ScreenLayout screenLayouts[2] = {
//    title       screen   screen   pixel    title       title    title menu    ship energy    ship energy    ship energy     ship energy    help          screen 
//                width    height   scale    location    scale    location      full pos       full size      empty pos       empty size     position      offset
    { "Phone"    ,256     ,384     ,3       ,{10, 88}   ,3.0f    ,{32, 248}    ,{240, 28}     ,{16, 328}     ,{240, 192}     ,{16,  0}      ,{   4, 360 } ,{  0,   0} },
    { "Desktop"  ,640     ,360     ,2       ,{64, 48}   ,4.0f    ,{32, 216}    ,{430,  4}     ,{210, 18}     ,{640,   4}     ,{ 0, 18}      ,{ 384, 348 } ,{192, -12} }
};

void switchBGMusic(Mix_Music* asset) {
	Mix_HaltMusic();
	if (asset) Mix_PlayMusic(asset, -1);
}

