#include "./EnemyBullet.h"
#include "./EnemyShot.h"
#include "../../engine/Global.h"

EnemyBullet::EnemyBullet() 
{ addModifier(new EnemyShot()); }

std::vector<Physics::Collision::Circle> EnemyBullet::getColliders() {
	std::vector<Physics::Collision::Circle> r;

	for (auto t : renderer.getInstances())
		r.push_back({ t.x, t.y, Bullet::radius });

	return r;
}

std::unordered_set<BulletHitable*> EnemyBullet::getHitables() {
	auto ret = std::unordered_set<BulletHitable*>();

	for(auto it : Global::world->allEnemyHitable())
		ret.emplace((BulletHitable*)it);

	return ret;
}

Bullet* EnemyBullet::newInstance() { return new EnemyBullet(); }
