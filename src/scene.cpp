#include "scene.h"

Scene::Scene() { active = true; };
bool Scene::isActive() { return active; }
void Scene::exit() { active = false; onEnd(); }
void Scene::restart() { active = true; onStart(); }

Scene::~Scene() {};


// Event handler overrideables
void Scene::onStart() {}
void Scene::onUpdate(olc::PixelGameEngine* pge, float dt) {}
void Scene::onDraw(olc::PixelGameEngine* pge) {}
void Scene::onEnd() {}
