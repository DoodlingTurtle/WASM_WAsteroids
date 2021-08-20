#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "./ship.h"

#include "config.h"
#include "olcPixelGameEngine.h"
#include "gameobject.h"
#include "spaceobj.h"
#include "collision.h"

#include <vector>


class Asteroid : public GameObject, public SpaceObj {

public:
    enum SIZES {
        SIZE_SMALL,
        SIZE_MIDDLE,
        SIZE_LARGE,
        SIZE_RANDOM
    };

    //creation
    Asteroid();
    ~Asteroid();
    void generateShape();
    void bringBackToLife(
        olc::vf2d pos, bool generateNewShape, 
        SIZES size,
        olc::vf2d direction = {0, 0},
        float velocity = -1 
    );

    // Implement SpaceObj
    void onDraw(olc::PixelGameEngine* pge) override;
    std::vector<SpaceObj*>* onUpdate(float deltaTime) override;

    // Getters
    SIZES getSize();
    std::vector<RGNDS::Collision::Circle> getColliders();
    olc::Sprite* getSprite();   

    // Setters
    void moveInDirection( float distance ) override;
    void markAsHit(const RGNDS::Collision*);


    static void spawn( 
        int nr, SIZES size = SIZE_RANDOM, 
        Ship* = nullptr,
        int x = 0, int y = 0, 
        olc::vf2d direction={0, 0}, float velocity=-1
    );

    void playSFX();

 protected:
    float spinSpeed = 0.10f;
    SIZES size;

 private:
    // Each asteroid consits of one sprite, which is created at the start of the game
    olc::Sprite* sprite;
    olc::Decal*  decal;
    
    bool killOnNextUpdate;
};
#endif
