#ifndef __GameWorld_H__
#define __GameWorld_H__

#define __HPP_HEADER__
#include "gameobject_components.hpp"
#undef __HPP_HEADER__

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include "gameobject.h"

#define GameObjectList std::unordered_set<GameObject*>

class GameWorld {
public:

    enum COMPONENT {
        COMP_GameObject,
        #define REGISTER_GO_COMPONENT(cla) COMP_ ## cla,
        #include "gameobject_components.hpp"
    };

    struct ObjList { GameObject* gameObject; };

    GameWorld();
    virtual~GameWorld();

    void addGameObject(GameObject*); 
    void removeGameObject(GameObject*); 

    int countWithAttribute(GameObject::ATTR);
    GameObjectList findByAttribute(GameObject::ATTR);
    void removeWithAttribute(GameObject::ATTR);

    #define REGISTER_GO_COMPONENT(T) std::unordered_set<T*> all##T();
    #include "gameobject_components.hpp"

    #define REGISTER_GO_COMPONENT(T) int count##T();
    #include "gameobject_components.hpp"

private:
    std::unordered_map<GameObject::ATTR, GameObjectList> attribute_maps; 
    #define REGISTER_GO_COMPONENT(T) std::unordered_set<T*> map_##T;
    #include "gameobject_components.hpp"

private:
    void addGOToAttribute(GameObject* go, GameObject::ATTR);

    friend class GameObject;

};

#endif
