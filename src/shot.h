#ifndef __SHOT_H__
#define __SHOT_H__

#include "olcPixelGameEngine.h"
#include "spaceobj.h"

#define MAX_SHOT_CNT 32

class Shot : public SpaceObj {

public:
    static std::vector<SpaceObj*>* shotGameObjects; 
    static std::vector<Shot*> getShots();
    static void Spawn(float angle, olc::vf2d* pos);
    static void cleanup();
    
    Shot();
    virtual ~Shot();

    void onDraw(SpaceObj::MainGameDrawData*);
    void onUpdate(SpaceObj::MainGameUpdateData*);

private:
    int lifetime = 1000;

};

#endif
