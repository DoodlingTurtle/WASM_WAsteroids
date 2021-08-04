#ifndef SHIP_H
#define SHIP_H 

#include "ship/shipstats.h"

#include <vector>

#include "../wraparoundrenderer.h"
#include "../spaceobj.h"

#include "shot.h"

#include "ship/shipupgrade.h"
#include "ship/shipstats.h"
#include "ship/shipengine.h"
#include "ship/shipupgrade_shield.h"
#include "ship/shipupgrade_shieldgenerator.h"
#include "../collision.h"

class Ship : public SpaceObj {
    public:

        Ship();
        ~Ship();

        void reset();

        void addUpgrade(ShipUpgrade* upgrade);

        std::vector<SpaceObj*>* onUpdate(float deltaTime);
        void onDraw(olc::PixelGameEngine*);

        bool shieldIsActive();

        RGNDS::Collision::Circle getCollider();

        olc::vf2d getPassiveVelocity();
        float getTravelDistance(float dt);

        olc::Sprite* getSprite();

    protected:
        ShipUpgrade_Shield* currentShield;

        ShipEngine                  shipEngine;
        ShipUpgrade_ShieldGenerator shieldgenerator;
        Shots                       shots;
        ShipStats*                  stats;

    private:

        void clearUpgrades();

        float angRes;
        bool thrusting;
        bool shieldIsUp;


        std::vector<ShipUpgrade*> upgrades;
        std::vector<ShipUpgrade*> newUpgrades; 

        olc::Sprite* sprDissolve;
        olc::Sprite* sprShip;
        olc::Decal*  decShip;
};







//#include "./particles.h"
/*class ShipExplosionParticle 
  : public ParticleSystem::Particle
  , public RGNDS::Transform 
{
public:
    static ShipExplosionParticle proto;

    ShipExplosionParticle();
    ~ShipExplosionParticle();

    bool update(float deltaTime);
    void attachToVector(float deltaTime, int renderIndex, std::vector<RGNDS::Point<double>>*);
    ShipExplosionParticle* getNewInstance(int index);


protected:
    float lifetime;
    float velocity;

};
*/
/*
class ShipExplosion : public ParticleSystem::Emitter, public SpaceObj {
public:
    ShipExplosion(Ship* ship);
    ~ShipExplosion();

    void onUpdate(SpaceObj::MainGameUpdateData*);
    void onDraw(SpaceObj::MainGameDrawData*);

    void onNoParticlesLeft();
};
*/
#endif // SHIP_H
