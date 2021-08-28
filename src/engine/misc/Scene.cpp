#include "../Scene.h"

namespace RGNDS {

	Scene::Scene( bool persistent ) : persistent(persistent) {};
	Scene::~Scene() {};


	// Event handler overrideables
	void Scene::onStart() {}
	bool Scene::onUpdate(olc::PixelGameEngine* pge, float dt) { return false; }
	void Scene::onDraw(olc::PixelGameEngine* pge) {}
	void Scene::onEnd() {}

}
