#pragma once

#include "../Engine.h"
#include "./components/Updateable.h"
#include "./components/Drawable.h"

#define __HPP_HEADER__
#include "gameobject_components.hpp"
#undef __HPP_HEADER__

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include "Object.h"

#define GameObjectList std::unordered_set<RGNDS::GameObject*>

namespace RGNDS {

	class GameWorld {
	public:
		enum COMPONENT {
			COMP_GameObject,
			COMP_Updateable,
			COMP_Drawable,
#define REGISTER_GO_COMPONENT(cla) COMP_ ## cla,
#include "gameobject_components.hpp"
		};

		struct ObjList { GameObject* gameObject; };

		GameWorld();
		virtual ~GameWorld();

		void addGameObject(GameObject*);

		int countWithAttribute(GameObject::ATTR);
		GameObjectList findByAttribute(GameObject::ATTR);
		void removeWithAttribute(GameObject::ATTR);

		std::unordered_set<World::Updateable*> allUpdateable();
		std::unordered_set<World::Drawable*> allDrawable();
#define REGISTER_GO_COMPONENT(T) std::unordered_set<T*> all##T();
#include "gameobject_components.hpp"


		int countUpdateable();
		int countDrawable();
#define REGISTER_GO_COMPONENT(T) int count##T();
#include "gameobject_components.hpp"

	private:
		std::unordered_map<GameObject::ATTR, GameObjectList> attribute_maps;

		std::unordered_set<World::Updateable*> map_Updateable;
		std::unordered_set<World::Drawable*> map_Drawable;
#define REGISTER_GO_COMPONENT(T) std::unordered_set<T*> map_##T;
#include "gameobject_components.hpp"

		std::vector<GameObject*> new_obj;

		void _addGameObject(GameObject*);
		void moveNew();
		void addGOToAttribute(GameObject* go, GameObject::ATTR);
		void removeGameObject(GameObject*);

		friend class RGNDS::GameObject;
		friend class RGNDS::Game;

	};
}
