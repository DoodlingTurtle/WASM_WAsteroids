#ifndef __ShipStats_H__
#define __ShipStats_H__

class ShipStats {
public: 
    ShipStats();


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

};

#endif
