#include "./PlayerBullet.h"

#include "../../engine/Global.h"

#include "../scorepopup.h"



std::unordered_set<BulletHitable*> PlayerBullet::getHitables() {
	auto ret = std::unordered_set<BulletHitable*>();

	for(auto it : Global::world->allPlayerHitable())
		ret.emplace((BulletHitable*)it);

	return ret;
}

Bullet* PlayerBullet::newInstance() { return new PlayerBullet(); }
