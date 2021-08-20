#ifndef __GameWorld_H__
#define __GameWorld_H__

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include "gameobject.h"

#define GameObjectList std::unordered_set<GameObject*>

class GameWorld {
public:

    struct ObjList { GameObject* gameObject; };

    GameWorld();
    virtual~GameWorld();

    void addGameObject(GameObject*); 
    void removeGameObject(GameObject*); 

    int countWithAttribute(GameObject::ATTR);
    GameObjectList findByAttribute(GameObject::ATTR);
    void removeWithAttribute(GameObject::ATTR);

private:
    std::unordered_map<GameObject::ATTR, GameObjectList> attribute_maps; 

private:
    void addGOToAttribute(GameObject* go, GameObject::ATTR);

    friend class GameObject;
};

#endif
