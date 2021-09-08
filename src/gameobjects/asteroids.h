#pragma once

#include "./ship.h"

#include "../config.h"
#include "../engine/olcPixelGameEngine.h"
#include "../engine/world/Object.h"
#include "../engine/physics/Collision.h"

#include "../spaceobj.h"

#include "../gamecomponents.h"

#include <vector>

using namespace RGNDS;

class Asteroid 
: public GameObject
, public World::Drawable 
, public World::Updateable
, public ShipShieldDeflectable
, public PlayerKiller
, public PlayerHitable
, public EnemyHitable
, public SpaceObj {

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
    void bringBackToLife(
        olc::vf2d pos, olc::PixelGameEngine* pge, 
        SIZES size,
        olc::vf2d direction = {0, 0},
        float velocity = -1 
    );

    // Implement Components
    void onDraw(olc::PixelGameEngine* pge) override;
    void onUpdate(float deltaTime) override;
    void gotDeflected(Ship*, ShipUpgrade_Shield*, Physics::Collision*) override;
    void hitByBullet(Bullet*, Physics::Collision*) override;
    int  getDestructionScore() override;


    // Getters
    SIZES getSize();
    std::vector<Physics::Collision::Circle> getColliders() override;
    olc::Sprite* getSprite();   

    // Setters
    void moveInDirection( float distance ) override;

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
