#include "BasicCannon.h"

#include <SDL/SDL_mixer.h>
#include "../../../engine/Global.h"
#include "../../../engine/Assets.h"

#include "../shipstats.h"
#include "../../ship.h"

using namespace RGNDS;

void BasicCannon::fire(ShipStats* stats, Ship* ship) {

	if (!stats->generatorhalt && stats->generator >= stats->shotenergyconsumption) {

		Global::world->addGameObject(stats->prototypeBullet->clone(
			ship->translate({16, 0}),
			ship->dir,
			std::max(0.0f, ship->moveVelocity * (ship->dir.dot(ship->getDirection())))
		));

		stats->generator -= stats->shotenergyconsumption;

		Mix_PlayChannel(-1, Assets::laser2, 0);

	}

}

void BasicCannon::onDraw(olc::PixelGameEngine* pge, ShipStats*, Ship* ship, RGNDS::Transform* tra) {
	pge->DrawPartialRotatedDecal(
		tra->pos, Assets::ship->Decal(), tra->ang, { 16.0f, 16.0f }, { 0.0f, 32.0f }, { 32.0f, 32.0f });
}
