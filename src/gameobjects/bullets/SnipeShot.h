#pragma once

#include "../bullet_modifier.h"
#include "../bullet.h"

class SnipeShot : public BulletModifier {
public:
    int updateScore(int currentScore, Bullet*);
};
