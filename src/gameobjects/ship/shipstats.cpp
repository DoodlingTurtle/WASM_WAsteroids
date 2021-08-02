#include "shipstats.h"

ShipStats::ShipStats() { resetToLV1(); }

void ShipStats::resetToLV1() {
    generatorcapacity = 90;
    generator = 90;
    shotenergyconsumption = 30;
    thrustenergyconsumption = 45;
    generatorrecovery = 30;
    shielduses = 0;
    generatorlock = 2;
    generatorunlock = 25;
    generatorhalt = false;
}
