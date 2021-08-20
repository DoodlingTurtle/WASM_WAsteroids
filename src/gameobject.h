#ifndef __GameObject_H__
#define __GameObject_H__

#include <vector>
#include <unordered_set>

class GameWorld;

#define GoAttr std::vector<GameObject::ATTR>

class GameObject {
public:
    
    enum ATTR {
        ALL,
        #undef REGISTER_GO_ATTR
        #define REGISTER_GO_ATTR(attr) attr,
        #include "./gameobject_attributes.hpp"
    };

    GameObject(std::vector<GameObject::ATTR> , bool persistent=false);
    virtual ~GameObject() = default;

    bool hasAttribute(GameObject::ATTR);

    void assignAttribute(GameObject::ATTR);

private:
    GameWorld* world;
    bool deleteWithWorld;
    std::unordered_set<ATTR> aAttributes;

    friend class GameWorld;
};

#endif
