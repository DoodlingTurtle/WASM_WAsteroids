#include "./SnipeShot.h"

int SnipeShot::updateScore(int currentScore, Bullet* b) {
	return currentScore * (1.0f + (1.0f - b->getLifetime()));
}
