#include "./gameworld.h"
#include "./config.h"

/*==============================================================================
 * GameWorld
 *============================================================================*/
GameWorld::GameWorld() {
    attribute_maps.emplace(GameObject::ALL, std::unordered_set<GameObject*>());

    #define REGISTER_GO_ATTR(a)\
        attribute_maps.emplace(GameObject::a, std::unordered_set<GameObject*>());
    #include "gameobject_attributes.hpp"

    #define REGISTER_GO_COMPONENT(a)\
        map_##a = std::unordered_set<a*>();
    #include "gameobject_components.hpp"
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

template <typename T>
static T* dcast(GameObject* go) { return dynamic_cast<T*>(go); }

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

    #define REGISTER_GO_COMPONENT(T) T* go_##T = dcast<T>(go);\
        if(go_##T) map_##T.emplace(go_##T); 
    #include "gameobject_components.hpp"

    go->world = this;
}

template<typename T>
static void clearMap(std::unordered_set<T*>* map, T* go) {
    auto it = map->find(go);
    if(it != map->end())
        map->erase(it);
}
void GameWorld::removeGameObject(GameObject* go) {

    Debug("GameWorld::removeGameObject");
    for(auto attr : go->aAttributes) {
        auto iterator = attribute_maps[attr].find(go);
        if(iterator != attribute_maps[attr].end()) {
            attribute_maps[attr].erase(iterator);
        }
    } 
    Debug("cleared Attributes");

    #define REGISTER_GO_COMPONENT(T) map_##T.erase(dynamic_cast<T*>(go)); Debug("clear map " << #T);
    #include "gameobject_components.hpp"

    Debug("cleared Compontents");

    Debug("GameObject" << " can be deleted " << go->deleteWithWorld);
    if(go->deleteWithWorld)
        delete go;
     
    Debug("GameObject " << go << " deleted (from world)");
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

#define REGISTER_GO_COMPONENT(T) int GameWorld::count##T() {\
    return map_##T.size(); }
#include "gameobject_components.hpp"

#define REGISTER_GO_COMPONENT(T) std::unordered_set<T*> GameWorld::all##T() {\
    return map_##T; }
#include "gameobject_components.hpp"
