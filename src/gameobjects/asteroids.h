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
   
	// A reference to the PixelGameEngine instances 
	// (in case an Asteroid needs to change its shape)
	static olc::PixelGameEngine* pge; 

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

        // Prints out the Sprite transformed via transform
        void init(olc::PixelGameEngine* pge);

        // Allows the Asteroid to change its shape
        void generateShape(olc::PixelGameEngine* pge);

        static std::function<void(int, void*)> onShipAction;

        void bringBackToLife(olc::PixelGameEngine* pge, olc::vf2d pos, bool generateNewShape, Asteroids::SIZES size);

        void onDraw(olc::PixelGameEngine* pge);
        void onUpdate(float deltaTime);

        short getScoreValue();

        Asteroids::SIZES getSize();

     protected:
        // Objects for Asteroid to keep track of
        static std::vector<Shot*> shots;
        float spinSpeed = 0.10f;

        Asteroids::SIZES size;

     private:
        static int sounds[4];

        // Each asteroid consits of one sprite, which is created at the start of the game
        olc::Sprite* sprite;

        // this defines the location, rotation and scale of the asteroid
        olc::GFX2D::Transform2D transform;
            
    };

    // Draw all asteroids via PGE Draw-Call
	void draw();

	// setup from game engine
	void init(olc::PixelGameEngine* engine);

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
