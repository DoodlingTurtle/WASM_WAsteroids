#include "config.h"

olc::Key GameKeyMap[11] = {
    olc::A,
    olc::D,
    olc::W,
    olc::S,
    olc::F,
    olc::K,
    olc::P,
    olc::K,
    olc::L,
    olc::J,
    olc::BACK
};

olc::Pixel pix_menubg = olc::Pixel(22, 36, 134, 200);
olc::Pixel pix_asteroid = olc::Pixel(138, 100, 73, 255);

int layer_asteroids = 0;
int layer_shots = 0;
int layer_stars = 0;
int layer_ship = 0;
int layer_blackout = 0;
int layer_particles = 0;

ScreenLayout screenLayouts[1] = {
    { "Portrait", 256, 384, 1, {10, 88}, {32, 272} }
};

