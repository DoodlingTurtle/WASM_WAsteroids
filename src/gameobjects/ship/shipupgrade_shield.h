#ifndef __ShipUpgrade_Shield_H__
#define __ShipUpgrade_Shield_H__

#include <SDL/SDL_mixer.h>

#include "../../transform.h"

#include "shipstats.h"
#include "shipupgrade.h"

#include "../asteroids.h"
#include "../../collision.h"
#include "../ship.h"

class ShipUpgrade_Shield: public ShipUpgrade 
{
public:
    ShipUpgrade_Shield();
    ~ShipUpgrade_Shield();

    bool init(ShipStats *shipstats) override;

    void draw(olc::PixelGameEngine*, RGNDS::Transform& ship) override;
    bool update(
            ShipStats* shipstats, Ship* ship 
          , float deltaTime
          , std::vector<SpaceObj*>* newSpaceObjects
    ) override;

    virtual float getRadius();

    void gotHit( Asteroids::Asteroid*, Ship* s, RGNDS::Collision*);

    static olc::Sprite* sprite;
    static olc::Decal*  decal;
    static Mix_Chunk*   sfxBump;

    static void init(olc::PixelGameEngine* pge);
    static void deinit();

private:
    float lifetime;
    float lastHitTime;
    double ang; 
    float rotspeed;
};

#endif
