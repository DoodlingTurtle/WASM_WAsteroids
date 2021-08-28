#include "./World.h"
#include "./Object.h"

namespace RGNDS {
	/*==============================================================================
	 * GameObject
	 *============================================================================*/

	GameObject::GameObject(
		std::vector<GameObject::ATTR> attributes,
		bool persistent
	)
		:persistent(persistent), world(nullptr)
	{
		for (auto attr : attributes)
			aAttributes.emplace(attr);

		aAttributes.emplace(GameObject::ALL);
	}

	bool GameObject::hasAttribute(GameObject::ATTR attr) {
		auto it = aAttributes.find(attr);

		return (it != aAttributes.end());
	}

	void GameObject::assignAttribute(GameObject::ATTR attr) {
		aAttributes.emplace(attr);

		if (world)
			world->addGOToAttribute(this, attr);
	}


	/*==============================================================================
	 * GameWorld
	 *============================================================================*/
	GameWorld::GameWorld() {

		new_obj = std::unordered_set<GameObject*>();

		attribute_maps.emplace(GameObject::ALL, std::unordered_set<GameObject*>());

#define REGISTER_GO_ATTR(a)\
        attribute_maps.emplace(GameObject::a, std::unordered_set<GameObject*>());
#include "../../gameobject_attributes.hpp"

		map_Updateable = std::unordered_set<World::Updateable*>();
		map_Drawable = std::unordered_set<World::Drawable*>();
#define REGISTER_GO_COMPONENT(a)\
        map_##a = std::unordered_set<a*>();
#include "../../gameobject_components.hpp"
	}

	GameWorld::~GameWorld() {
		auto list = attribute_maps[GameObject::ALL];
		for (auto go : list)
			if (go->persistent)
				delete go;
	}

	GameObjectList GameWorld::findByAttribute(GameObject::ATTR attr) {
		return attribute_maps[attr];
	}

	int GameWorld::countWithAttribute(GameObject::ATTR attr) {
		return attribute_maps[attr].size();
	}

	void GameWorld::addGameObject(GameObject* go) {
		new_obj.emplace(go);
	}

	void GameWorld::moveNew() {
		for (auto go : new_obj)
			_addGameObject(go);
	}

	template <typename T>
	static T* dcast(GameObject* go) { return dynamic_cast<T*>(go); }
	void GameWorld::_addGameObject(GameObject* go) {
		// If object is part of another world remove it from that world first
		if (go->world) {
			bool pers = go->persistent;
			go->persistent = true;
			go->world->removeGameObject(go);
			go->persistent = pers;
		}

		for (auto attr : go->aAttributes)
			attribute_maps.find(attr)->second.emplace(go);

		World::Updateable* go_Updateable = dcast<World::Updateable>(go);
		if (go_Updateable) map_Updateable.emplace(go_Updateable);

		World::Drawable* go_Drawable = dcast<World::Drawable>(go);
		if (go_Drawable) map_Drawable.emplace(go_Drawable);

#define REGISTER_GO_COMPONENT(T) T* go_##T = dcast<T>(go);\
        if(go_##T) map_##T.emplace(go_##T); 
#include "gameobject_components.hpp"

		go->world = this;
	}

	template<typename T>
	static void clearMap(std::unordered_set<T*>* map, T* go) {
		auto it = map->find(go);
		if (it != map->end())
			map->erase(it);
	}
	void GameWorld::removeGameObject(GameObject* go) {

		for (auto attr : go->aAttributes) {
			auto iterator = attribute_maps[attr].find(go);
			if (iterator != attribute_maps[attr].end()) {
				attribute_maps[attr].erase(iterator);
			}
		}

		map_Updateable.erase(dynamic_cast<World::Updateable*>(go));
		map_Drawable.erase(dynamic_cast<World::Drawable*>(go));

#define REGISTER_GO_COMPONENT(T) map_##T.erase(dynamic_cast<T*>(go)); 
#include "gameobject_components.hpp"

		if (!go->persistent)
			delete go;

	}

	void GameWorld::removeWithAttribute(GameObject::ATTR attr) {
		auto list = findByAttribute(attr);
		for (auto go : list)
			go->assignAttribute(GameObject::DEAD);
	}

	void GameWorld::addGOToAttribute(GameObject* go, GameObject::ATTR attr) {
		if (go->world != this) throw "GO is not part of this world";
		attribute_maps[attr].emplace(go);
	}

	int GameWorld::countUpdateable() { return map_Updateable.size(); }
	int GameWorld::countDrawable() { return map_Drawable.size(); }
#define REGISTER_GO_COMPONENT(T) int GameWorld::count##T() {\
    return map_##T.size(); }
#include "../../gameobject_components.hpp"

	std::unordered_set<World::Updateable*> GameWorld::allUpdateable() { return map_Updateable; }
	std::unordered_set<World::Drawable*> GameWorld::allDrawable()   { return map_Drawable; }
#define REGISTER_GO_COMPONENT(T) std::unordered_set<T*> GameWorld::all##T() {\
    return map_##T; }
#include "../../gameobject_components.hpp"
}
