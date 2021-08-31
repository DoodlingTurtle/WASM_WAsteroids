#ifndef __ShipStats_H__
#define __ShipStats_H__

#include <vector>
#include "./ship_component.h"
#include "./ShipCannon.h"

#include "gameobjects/bullet.h"

class ShipStats {
public: 
    ShipStats();
    virtual ~ShipStats();

    float generatorcapacity;
    float generator;
    float generatorlock;
    float generatorunlock;
    float shotenergyconsumption;
    float thrustenergyconsumption;
    float generatorrecovery;
    
    bool generatorhalt;

    void resetToLV1();

    void giveComponentsTo(std::vector<ShipComponent*>*);
    void takeComponentsFrom(std::vector<ShipComponent*>*);

    void registerNewComponent(ShipComponent* comp);

    Bullet*     prototypeBullet;
    ShipCannon* shipCannon;

protected:
    std::vector<ShipComponent*> components;

};

#endif
