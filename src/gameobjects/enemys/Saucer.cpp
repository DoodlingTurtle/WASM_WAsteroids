#include "./Saucer.h"

#include <math.h>

#include "../player_ship.h"
#include "../../engine/Global.h"
#include "../../engine/Assets.h"

#include "../../particles/ship_explosion.h"
#include "../bullets/EnemyBullet.h"

/* every x seconds */
#define FIRE_RATE 0.750

using namespace RGNDS;

Saucer::Saucer()
	: Ship(olc::Sprite(32, 32))
	, deltaTimeAccumu(0.0f)
	, fireRateDeltaTime(0.0f)
{
	Global::game->SetDrawTarget(&sprDissolve);
	Global::game->DrawPartialSprite({ 0, 0 }, Assets::ship->Sprite(), { 0, 64 }, { 32, 32 });
	Global::game->SetDrawTarget(nullptr);

	setDirection({ 1, 0 }); // TODO: Randomize direction between left and right
	moveVelocity = 32.0f;   // TODO: Randomize this too
	pos = {					// TODO: Randomize start position based on move direction
		0,
		Global::layout->app_height / 2.0f
	};

	assignAttribute(GameObject::SAUCER);
}
Saucer::~Saucer() { }

void Saucer::onUpdate(float deltaTime) {
	// Update timers
	deltaTimeAccumu = std::fmod(deltaTimeAccumu + deltaTime, 2.0f); // Animation
	fireRateDeltaTime += deltaTime;                                 // fire

	// mark dead, if saucer leaves the screen
	if ( pos.x < 0 || pos.x > Global::layout->app_width ||
		pos.y < 0 || pos.y > Global::layout->app_height) 
	{ this->assignAttribute(GameObject::DEAD); }

	// fire bullet
	if (fireRateDeltaTime >= FIRE_RATE) {
		// make sure player is on screen
		auto lst = Global::world->findByAttribute(GameObject::PLAYER_SHIP);
		auto it = lst.begin();

		if (it != lst.end()) {
			PlayerShip* s = (PlayerShip*)(*it);

			auto bullet = new EnemyBullet();
			bullet->pos = this->pos;
			bullet->pointTowardsPosition(s->pos);
			bullet->moveVelocity = 96.0f; // TODO: Increase with difficulty

			Global::world->addGameObject(bullet);
		}
		fireRateDeltaTime -= FIRE_RATE;
	}

	else Ship::onUpdate(deltaTime);
}

std::vector<Physics::Collision::Circle> Saucer::getColliders() {
	auto lst = std::vector<Physics::Collision::Circle>();
	lst.push_back(Ship::getCollider());
	return lst;
}

void Saucer::hitByBullet(Bullet*, Physics::Collision*) {
	assignAttribute(GameObject::DEAD);
	Global::world->addGameObject(new ShipExplosion(this));
}

int Saucer::getDestructionScore() { return 450; }

void Saucer::onDraw(olc::PixelGameEngine* pge) {
	pge->DrawPartialRotatedDecal(
		this->pos, Assets::ship->Decal(), 0.0f, {16.0f, 16.0f},
		{ std::floor(deltaTimeAccumu) * 32, 64 }, { 32, 32 }
	);
}
