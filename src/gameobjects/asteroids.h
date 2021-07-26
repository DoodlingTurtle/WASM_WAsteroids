#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "../config.h"
#include "../olcPixelGameEngine.h"
#include "../olcPGEX_Graphics2D.h"
#include "../spaceobj.h"

#include "shot.h"

#include <vector>

class Asteroids {

public:
   
    enum SIZES {
        SIZE_SMALL,
        SIZE_MIDDLE,
        SIZE_LARGE,
        SIZE_RANDOM
    };

    class Asteroid : public SpaceObj {

    public:
        Asteroid();
        ~Asteroid();

        // Allows the Asteroid to change its shape
        void generateShape();

        static std::function<void(int, void*)> onShipAction;

        void bringBackToLife(olc::vf2d pos, bool generateNewShape, Asteroids::SIZES size);

        void onDraw(olc::PixelGameEngine* pge);
        std::vector<SpaceObj*>* onUpdate(float deltaTime);

        short getScoreValue();

        Asteroids::SIZES getSize();

     protected:
        // Objects for Asteroid to keep track of
        //static std::vector<Shot*> shots;
        float spinSpeed = 0.10f;

        Asteroids::SIZES size;

     private:
        static int sounds[4];

        // Each asteroid consits of one sprite, which is created at the start of the game
        olc::Sprite* sprite;
            
    };

    // Draw all asteroids via PGE Draw-Call
	void draw();

    // Update all asteroids
    void update(float deltaTime);

    // makes a certain number of Asteroids appear.
    std::vector<Asteroid*>* spawnAsteroids( 
        int nr, 
        Asteroids::SIZES size = SIZE_RANDOM, 
        int x = 0, int y = 0
    );

    // remove all Asteroids from the playfield
    void killall();

    // Check if a given Pointer belongs to one of the asteroids
    Asteroid* isAsteroid(void*);
    

private:
	// reserve Memory to store all asteroids in the game
	Asteroid asteroids[MAX_ASTEROIDS];


};



#endif
