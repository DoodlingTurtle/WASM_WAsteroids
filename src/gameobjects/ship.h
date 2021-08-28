#pragma once

#include <vector>
#include <SDL/SDL_mixer.h>
#include "../engine/olcPixelGameEngine.h"
#include "../engine/world/Object.h"
#include "../engine/world/components/Drawable.h"
#include "../engine/world/components/Updateable.h"
#include "../engine/physics/Collision.h"

#include "./ship/shipstats.h"
#include "./ship/shipupgrade.h"
#include "./ship/shipstats.h"
#include "./ship/shipengine.h"

#include "../wraparoundrenderer.h"
#include "../spaceobj.h"

class ShipUpgrade_Shield;
using namespace RGNDS;

class Ship : 
      public GameObject
    , public World::Drawable
    , public World::Updateable
    , public SpaceObj 
{
    public:

        Ship();
        ~Ship();
        void reset();

        void onUpdate(float deltaTime) override;
        void onDraw(olc::PixelGameEngine*) override;

        // Getters
        Physics::Collision::Circle getCollider();
        olc::Sprite* getSprite();  // Gets a sprite representing the ship

        // Upgrade related stuff
        void addUpgrade(ShipUpgrade* upgrade);
        bool shieldIsActive();

    protected:
        ShipUpgrade_Shield* currentShield;    // keeps track, which updgrade is the current shield

        // Ship Sub functions
        ShipEngine                  shipEngine;
        ShipStats*                  stats;

    private:

        void clearUpgrades(); // removes and deletes all installed upgrades

        float angRes;      // defines how fast the ship can turn per sec.
        bool  thrusting;   // defines if the ship is accelerating

        std::vector<ShipUpgrade*> upgrades;
        std::vector<ShipUpgrade*> newUpgrades; 
        std::vector<ShipComponent*> components;

        olc::Sprite* sprDissolve;
        int          chaThrust;    // keeps track on what channel the thrusting sound is playing

        std::vector<int> selectableComponents;  // A list of indexes in this->components, that is invoceable bz the plazer
        int              selectedComponent;     // the currently selected component in selectableComponents
};
