#ifndef __ShipUpgrade_ShieldGenerator_H__
#define __ShipUpgrade_ShieldGenerator_H__

#include "../../transform.h"

#include "shipstats.h"
#include "shipupgrade.h"
#include "shipupgrade_shield.h"

class ShipUpgrade_ShieldGenerator : public ShipUpgrade {
public:
    ShipUpgrade_ShieldGenerator();
    virtual~ShipUpgrade_ShieldGenerator();

    bool init(ShipStats* stats); 
    bool update(ShipStats* shipstats, Ship* ship, float deltaTime);
    void draw(RGNDS::Transform& ship); 

//    static ShipUpgrade_Shield shield;

protected:

private:
    int* uses;
    int* controls;
    bool deployShield;

};

#endif
