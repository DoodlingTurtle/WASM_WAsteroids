#ifndef __ShipUpgrade_Cannon_H__
#define __ShipUpgrade_Cannon_H__

#include "shipupgrade.h"
#include "shipstats.h"
#include "../shot.h"
#include "../ship.h"

class ShipUpgrade_Cannon : public ShipUpgrade {
public:
    ShipUpgrade_Cannon();
    virtual~ShipUpgrade_Cannon();
    
    bool init(ShipStats* stats) override;
    void draw(olc::PixelGameEngine*, RGNDS::Transform& ship) override ;
    bool update(
            ShipStats* shipstats, Ship* ship 
          , float deltaTime
          , std::vector<SpaceObj*>* newSpaceObjects
    ) override ;

protected:
    Shots shots;

private:

};

#endif