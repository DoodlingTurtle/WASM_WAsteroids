#include "scene.h"

Scene::Scene() { active = true; };
bool Scene::isActive() { return active; }
void Scene::exit() { active = false; }
Scene::~Scene() {};

void Scene::onStart() {}
void Scene::onUpdate(olc::PixelGameEngine* pge, float dt) {}
void Scene::onDraw(olc::PixelGameEngine* pge) {}
void Scene::onEnd() {}
