#include "shipstats.h"

ShipStats::ShipStats() 
:prototypeBullet(nullptr)
{ resetToLV1(); }

static void _clearComponents(std::vector<ShipComponent*> &components) {
    for(auto c : components)
        delete c;

    components.clear();
}

ShipStats::~ShipStats() {
    _clearComponents(components);
}

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

    _clearComponents(components);

    if(prototypeBullet)
        delete prototypeBullet;

    prototypeBullet = new Bullet();
}


static void _transfereComponents(
    std::vector<ShipComponent*>* from, 
    std::vector<ShipComponent*>* to
) {

    for(int a = 0; a < from->size(); a++)
        to->push_back(from->at(a));

    from->clear();
};

void ShipStats::giveComponentsTo(std::vector<ShipComponent*>* a)
{ _transfereComponents(&components, a); }

void ShipStats::takeComponentsFrom(std::vector<ShipComponent*>* a)
{ 
    _transfereComponents(a, &components); 
    
    for(int a = components.size()-1; a>=0; a--){
        ShipComponent* comp = components.at(a);
        if(comp) {
            if(!comp->deinitShipComponent(this)) {
                delete comp;
                comp = nullptr;
            }
        }
        
        if(!comp)
            components.erase(components.begin() + a);     
    }
}

void ShipStats::registerNewComponent(ShipComponent* comp) {
    components.push_back(comp);
}
