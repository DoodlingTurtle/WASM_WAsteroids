#pragma once

#include "../bullet_modifier.h"

class EnemyShot : public BulletModifier {
	// Inherited via BulletModifier
	virtual int updateScore(int currentScore, Bullet*) override;
};
