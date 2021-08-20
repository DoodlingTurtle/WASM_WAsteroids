#ifndef __Bullet_H__
#define __Bullet_H__

#include "olcPixelGameEngine.h"
#include "bullet_modifier.h"
#include "gameobject.h"
#include "spaceobj.h"

class Bullet : public GameObject, public SpaceObj {
public:
    struct DecalRect { olc::vf2d coords, size; };

    Bullet(
            float lifetime = 1.0f, 
            const DecalRect = {{0, 0}, {6, 6}}, 
            float radius = 2.0f
    );
    virtual~Bullet();
    
    void onDraw(olc::PixelGameEngine*) override;
    std::vector<SpaceObj*>* onUpdate(float deltaTime) override;
   
    Bullet* clone(olc::vf2d pos, olc::vf2d dir, float acceleration);

protected:
    static olc::Renderable spriteSheet;
    float lifetime, radius;
    std::vector<BulletModifier*> modifiers;

    DecalRect decalCoords;
};

#endif

