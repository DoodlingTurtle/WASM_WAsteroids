#include "BasicCannon.h"

#include <SDL/SDL_mixer.h>
#include "../../../engine/Global.h"
#include "../../../engine/Assets.h"

#include "../shipstats.h"
#include "../../ship.h"

using namespace RGNDS;

void BasicCannon::fire(ShipStats* stats, Ship* ship) {

	if (!stats->generatorhalt && stats->generator >= stats->shotenergyconsumption) {

		Bullet* b = stats->prototypeBullet->clone(ship->pos, ship->dir,
			std::max(0.0f, ship->moveVelocity * (ship->dir.dot(ship->getDirection())))
		);
		b->movePixelDistance(16);
		Global::world->addGameObject(b);
		stats->generator -= stats->shotenergyconsumption;

		Mix_PlayChannel(-1, Assets::bullet_fire_1, 0);
	}

}

void BasicCannon::onDraw(olc::PixelGameEngine* pge, ShipStats*, Ship* ship) {
	ship->draw([this](RGNDS::Transform* tra) {
		Global::game->DrawPartialRotatedDecal(
			tra->pos, Assets::ship->Decal(), tra->ang, { 16.0f, 16.0f }, { 0.0f, 32.0f }, { 32.0f, 32.0f });
	});
}
