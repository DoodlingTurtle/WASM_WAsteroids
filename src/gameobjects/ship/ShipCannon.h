#pragma once

#include "../../engine/olcPixelGameEngine.h"
#include "../../engine/Transform.h"

class Ship;
class ShipStats;

class ShipCannon {
public:
	virtual void fire(ShipStats*, Ship*) = 0;
	virtual void onDraw(olc::PixelGameEngine* pge, ShipStats*, Ship*, RGNDS::Transform* tr) {};
};
