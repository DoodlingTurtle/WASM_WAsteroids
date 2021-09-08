#pragma once

#include "../bullet.h"
#include "../../gamecomponents.h"

class EnemyBullet : public Bullet, public PlayerKiller {
public:
	EnemyBullet();

	// Inherited via PlayerKiller
	virtual std::vector<Physics::Collision::Circle> getColliders() override;

	// Inherited via Bullet
	virtual std::unordered_set<BulletHitable*> getHitables() override;
	virtual Bullet* newInstance() override;
};
