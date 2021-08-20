#include "./gameworld.h"

/*==============================================================================
 * GameWorld
 *============================================================================*/
GameWorld::GameWorld() {
    attribute_maps.emplace(GameObject::ALL, std::unordered_set<GameObject*>());

    #undef REGISTER_GO_ATTR
    #define REGISTER_GO_ATTR(a) attribute_maps.emplace(GameObject::a, std::unordered_set<GameObject*>());
    #include "gameobject_attributes.hpp"
}

GameWorld::~GameWorld() {
    auto list = attribute_maps[GameObject::ALL];
    for(auto go : list)
        if(go->deleteWithWorld)
            delete go;

}

GameObjectList GameWorld::findByAttribute(GameObject::ATTR attr) {
    return attribute_maps[attr];
}

int GameWorld::countWithAttribute(GameObject::ATTR attr) {
    return attribute_maps[attr].size();
}

void GameWorld::addGameObject(GameObject* go) {
    // If object is part of another world remove it from that world first
    if(go->world) {
        bool pers = go->deleteWithWorld;
        go->deleteWithWorld = false;
        go->world->removeGameObject(go);
        go->deleteWithWorld = pers;
    }

    for(auto attr : go->aAttributes) 
        attribute_maps.find(attr)->second.emplace(go);

    go->world = this;
}

void GameWorld::removeGameObject(GameObject* go) {

    for(auto attr : go->aAttributes) {
        auto gl = attribute_maps[attr];
        auto iterator = gl.find(go);
        if(iterator != gl.end()) 
            gl.erase(iterator); 
    }

    if(go->deleteWithWorld)
        delete go;
}

void GameWorld::removeWithAttribute(GameObject::ATTR attr) {
    auto list = findByAttribute(attr);
    for(auto go : list)
        removeGameObject(go);
} 

void GameWorld::addGOToAttribute(GameObject* go, GameObject::ATTR attr) {
    if(go->world != this) throw "GO is not part of this world";
    attribute_maps[attr].emplace(go);
}

