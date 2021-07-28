#ifndef __SHOT_H__
#define __SHOT_H__

#include "../config.h"
#include "../olcPixelGameEngine.h"
#include "../spaceobj.h"

#include <vector>


class Shots {
public:
    
    class Shot : public SpaceObj {

    public:
        static void cleanup();
        
        Shot();
        virtual ~Shot();

        void onDraw(olc::PixelGameEngine*) override;
        std::vector<SpaceObj*>* onUpdate(float deltaTime) override;

        void revive(olc::vf2d* pos, float ang, olc::Decal*);

        olc::Decal* decal;

    private:
        int lifetime = 1000;

    };
   
    Shots();
    ~Shots();


    // create new Shot - instances
    Shot* spawnShot(float angle, olc::vf2d* pos);

    // disables all possible shot instances
    void killall();


    // Sprite, that is used to draw each shot
    olc::Sprite* sprShot;
    olc::Decal * decShot;

private:
    Shot shots[MAX_SHOT_CNT];

};

#endif
