#ifndef SHIP_H
#define SHIP_H 

#include <vector>
#include <SDL/SDL_mixer.h>

#include "ship/shipstats.h"


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

        // Implement SpaceObj
        std::vector<SpaceObj*>* onUpdate(float deltaTime) override;
        void onDraw(olc::PixelGameEngine*) override;

        // Getters
        RGNDS::Collision::Circle getCollider();
        olc::Sprite* getSprite();  // Gets a sprite representing the ship

        // Upgrade related stuff
        void addUpgrade(ShipUpgrade* upgrade);
        bool shieldIsActive();

        void kill() override;

    protected:
        ShipUpgrade_Shield* currentShield;    // keeps track, which updgrade is the current shield

        // Ship Sub functions
        ShipEngine                  shipEngine;
        Shots                       shots;
        ShipStats*                  stats;

    private:

        void clearUpgrades(); // removes and deletes all installed upgrades

        float angRes;      // defines how fast the ship can turn per sec.
        bool  thrusting;   // defines if the ship is accelerating

        std::vector<ShipUpgrade*> upgrades;
        std::vector<ShipUpgrade*> newUpgrades; 

        olc::Sprite* sprDissolve;
        olc::Sprite* sprShip;
        olc::Decal*  decShip;

        Mix_Chunk*   sfxExplode;   // SDL_Mixer SFX asset
        Mix_Chunk*   sfxThrust;    // SDL_Mixer SFX asset
        int          chaThrust;    // keeps track on what channel the thrusting sound is playing
};


#endif // SHIP_H
