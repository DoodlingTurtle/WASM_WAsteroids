#pragma once

#include <vector>
#include "spaceobj.h"

class Bullet;

class BulletModifier {
public:
    virtual int updateScore(int currentScore, Bullet*) = 0;

};
