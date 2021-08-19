#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "config.h"
#include "olcPixelGameEngine.h"
#include "spaceobj.h"
#include "collision.h"

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
        //creation
        Asteroid();
        ~Asteroid();
        void generateShape();
        void bringBackToLife(
            olc::vf2d pos, bool generateNewShape, 
            Asteroids::SIZES size,
            olc::vf2d direction = {0, 0},
            float velocity = -1 
        );

        // Implement SpaceObj
        void onDraw(olc::PixelGameEngine* pge) override;
        std::vector<SpaceObj*>* onUpdate(float deltaTime) override;

        // Getters
        Asteroids::SIZES getSize();
        std::vector<RGNDS::Collision::Circle> getColliders();
        olc::Sprite* getSprite();   

        // Setters
        void moveInDirection( float distance ) override;
        void markAsHit(const RGNDS::Collision*);

        bool allowDeleteAfterDeath() override;

     protected:
        float spinSpeed = 0.10f;
        Asteroids::SIZES size;

     private:
        // Each asteroid consits of one sprite, which is created at the start of the game
        olc::Sprite* sprite;
        olc::Decal*  decal;
        
        bool killOnNextUpdate;
    };

    Asteroids();
    virtual ~Asteroids();


    // Draw all asteroids via PGE Draw-Call
	void draw();

    // Update all asteroids
    void update(float deltaTime);

    // makes a certain number of Asteroids appear.
    std::vector<Asteroid*>* spawnAsteroids( 
        int nr, Asteroids::SIZES size = SIZE_RANDOM, 
        int x = 0, int y = 0, 
        olc::vf2d direction={0, 0}, float velocity=-1
    );

    // remove all Asteroids from the playfield
    void killall();

    // Check if a given Pointer belongs to one of the asteroids
    Asteroid* isAsteroid(void*);    

    std::vector<Asteroid*> getLiveAsteroids();
    void markDirty();

    std::vector<RGNDS::Collision::Circle> getActiveColliders();

    void playSFX();

private:
	// reserve Memory to store all asteroids in the game
	Asteroid asteroids[MAX_ASTEROIDS];

    // a list of life ansteroids
    std::vector<Asteroid*> liveAsteroids;

    // defines if the list of live asteroids must be refreshed
    bool dirty;

};



#endif
