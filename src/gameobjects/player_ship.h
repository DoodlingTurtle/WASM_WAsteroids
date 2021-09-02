#pragma once

#include <vector>
#include <SDL/SDL_mixer.h>

#include "./ship.h"

#include "./ship/shipstats.h"
#include "./ship/ship_component.h"

using namespace RGNDS;

class PlayerShip : public Ship
{
public:
	PlayerShip();
	~PlayerShip();
	void reset();

	void onUpdate(float deltaTime) override;
	void onDraw(olc::PixelGameEngine*) override;

protected:
	// Ship Sub functions
	ShipEngine                  shipEngine;
	ShipStats* stats;

private:
	std::vector<int> selectableComponents;  // A list of indexes in this->components, that is invoceable bz the plazer
	int              selectedComponent;     // the currently selected component in selectableComponents
	bool			 thrusting;				// defines if the ship is accelerating

	std::vector<ShipComponent*> components;
	int          chaThrust;    // keeps track on what channel the thrusting sound is playing
};
