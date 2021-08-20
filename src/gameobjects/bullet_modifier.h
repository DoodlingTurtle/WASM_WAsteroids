#ifndef __BulletModifier_H__
#define __BulletModifier_H__

#include <vector>
#include "spaceobj.h"

class Bullet;

class BulletModifier {
public:
    virtual int updateScore(int currentScore, Bullet*) = 0;

};

#endif