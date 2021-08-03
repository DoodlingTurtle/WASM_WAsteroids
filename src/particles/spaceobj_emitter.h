#ifndef __SpaceObj_Emitter_H__
#define __SpaceObj_Emitter_H__

#include "../particles.h"
#include "../transform.h"
#include "../spaceobj.h"

template <typename Pa>
class SpaceObj_Emitter 
: public ParticleSystem<SpaceObj_Emitter<Pa>, Pa>::Emitter
, public RGNDS::Transform
{
public:
    SpaceObj_Emitter(int x, int y, float scale, SpaceObj* system) {
        pos.x = x;
        pos.y = y;
        this->scale = scale;
        this->system  = system;
    };

    void onNoParticlesLeft() override { system->kill(); };

private:
    SpaceObj* system;

};

#endif
