#pragma once

#include <vector>
#include <SDL/SDL_mixer.h>
#include "../engine/olcPixelGameEngine.h"
#include "../engine/world/Object.h"
#include "../engine/world/components/Drawable.h"
#include "../engine/world/components/Updateable.h"
#include "../engine/physics/Collision.h"

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

        Ship(olc::Sprite dissoveSprite = olc::Sprite{0, 0});
        ~Ship();

        void onUpdate(float deltaTime) override;
        void drawUpgrades(olc::PixelGameEngine*, RGNDS::Transform*);

        // Getters
        Physics::Collision::Circle getCollider();
        olc::Sprite* getSprite();  // Gets a sprite representing the ship

        // Upgrade related stuff
        void addUpgrade(ShipUpgrade* upgrade);
        

        bool shieldIsActive();

    protected:
        ShipUpgrade_Shield* currentShield;    // keeps track, which updgrade is the current shield
        olc::Sprite         sprDissolve;
        void clearUpgrades(); // removes and deletes all installed upgrades
        float angRes;      // defines how fast the ship can turn per sec.

    private:
        std::vector<ShipUpgrade*> upgrades;
        std::vector<ShipUpgrade*> newUpgrades; 


};
