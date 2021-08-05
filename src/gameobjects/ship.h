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


#endif // SHIP_H
