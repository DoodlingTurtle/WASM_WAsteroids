#pragma once

#include "../ShipCannon.h"

class BasicCannon : public ShipCannon {
public:
	// Inherited via ShipCannon
	virtual void fire(ShipStats*, Ship*) override;

	void onDraw(olc::PixelGameEngine*, ShipStats*, Ship*, RGNDS::Transform* tr) override;


};
