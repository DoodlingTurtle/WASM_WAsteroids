#pragma once

#include "../bullet.h"

class PlayerBullet : public Bullet {
	// Inherited via Bullet
	virtual std::unordered_set<BulletHitable*> getHitables() override;
	virtual Bullet* newInstance() override;
};
