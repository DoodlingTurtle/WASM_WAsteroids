#ifndef __ShipStats_H__
#define __ShipStats_H__

#include <vector>
#include "ship_component.h"

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
    int shielduses;

    void resetToLV1();

    void giveComponentsTo(std::vector<ShipComponent*>*);
    void takeComponentsFrom(std::vector<ShipComponent*>*);

    void registerNewComponent(ShipComponent* comp);

protected:
    std::vector<ShipComponent*> components;

};

#endif
