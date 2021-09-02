#pragma once

#include "../ShipCannon.h"

class Ship;
class ShipStats;

class DualCannon : public ShipCannon {
	virtual void fire(ShipStats*, Ship*);
	void onDraw(olc::PixelGameEngine* pge, ShipStats* stats, Ship* ship, RGNDS::Transform* tr) override;
};
