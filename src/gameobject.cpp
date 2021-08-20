#include "gameobject.h"
#include "gameworld.h"

GameObject::GameObject(
        std::vector<GameObject::ATTR> attributes, 
        bool persistent
) 
:deleteWithWorld(!persistent), world(nullptr) 
{ 
    for(auto attr : attributes)
        aAttributes.emplace(attr);

    aAttributes.emplace(GameObject::ALL);
} 

bool GameObject::hasAttribute(GameObject::ATTR attr) {
    auto it = aAttributes.find(attr);

    return (it != aAttributes.end());
}

void GameObject::assignAttribute(GameObject::ATTR attr) {
    aAttributes.emplace(attr);

    if(world)
        world->addGOToAttribute(this, attr);
}
