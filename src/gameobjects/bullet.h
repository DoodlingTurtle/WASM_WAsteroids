#pragma once

#include "../engine/olcPixelGameEngine.h"
#include "../engine/world/Object.h"
#include "../engine/world/components/Drawable.h"
#include "../engine/world/components/Updateable.h"

#include "./bullet_modifier.h"
#include "../gamecomponents.h"
#include "../spaceobj.h"

using namespace RGNDS;

class Bullet 
    : public GameObject
    , public World::Drawable
    , public World::Updateable
    , public SpaceObj 
{
public:
    struct DecalRect { olc::vf2d coords, size; };

    Bullet(
            float lifetime = 1.0f, 
            const DecalRect = {{0, 0}, {6, 6}}, 
            float radius = 2.0f
    );
    virtual~Bullet();
    
    void onDraw(olc::PixelGameEngine*) override;
    void onUpdate(float deltaTime) override;
   
    Bullet* clone(olc::vf2d pos, olc::vf2d dir, float acceleration);

    float getLifetime();

    void addModifier(BulletModifier*);

    virtual std::unordered_set<BulletHitable*> getHitables() = 0;
    virtual Bullet* newInstance() = 0;

protected:
    float totalLifetime, lifetime, radius;
    std::vector<BulletModifier*> modifiers;
    DecalRect decalCoords;

private:
    bool isClone;

};
