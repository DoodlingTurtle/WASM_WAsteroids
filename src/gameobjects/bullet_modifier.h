#pragma once

#include <vector>

class Bullet;

class BulletModifier {
public:
    virtual int updateScore(int currentScore, Bullet*) = 0;

};
