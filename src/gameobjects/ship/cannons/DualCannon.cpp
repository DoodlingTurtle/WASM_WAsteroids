#include "./DualCannon.h"
#include "../../../engine/Assets.h"
#include "./../shipstats.h"
#include "../../ship.h"
#include "../../../engine/Global.h"
#include "../../../engine/Assets.h"
#include "../../../engine/olcPixelGameEngine.h"

void DualCannon::fire(ShipStats* stats, Ship* ship) {
	if (stats->generator < stats->shotenergyconsumption) return;

	float accell = std::max(0.0f, ship->moveVelocity * (ship->dir.dot(ship->getDirection())));

	Global::world->addGameObject(
		stats->prototypeBullet->clone( 
			ship->translate({4, -8}) , 
			ship->dir, accell 
		)
	);

	Global::world->addGameObject(
		stats->prototypeBullet->clone( 
			ship->translate({4, 8}) , 
			ship->dir, accell 
		)
	);

	stats->generator -= stats->shotenergyconsumption;

	Mix_PlayChannel(-1, Assets::laser1, 0);
}

void DualCannon::onDraw(olc::PixelGameEngine* pge, ShipStats* stats, Ship* ship, RGNDS::Transform* tra) {
	pge->DrawPartialRotatedDecal(
		tra->pos, Assets::ship->Decal(), tra->ang, { 16.0f, 16.0f }, { 32.0f, 32.0f }, { 32.0f, 32.0f });
}
