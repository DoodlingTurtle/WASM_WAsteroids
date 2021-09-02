#include "./ship.h"

#include <math.h>
#include <stdio.h>

#include "../config.h"
#include "../engine/Global.h"
#include "../engine/physics/Collision.h"
#include "../engine/Assets.h"

#include "./ship/shipupgrade_shield.h"
#include "../particles/ship_explosion.h"


#ifdef DEBUG_BUILD
#include "../engine/ui/DebugOverlay.h"
#endif

#define SHIP_MAX_VELOCITY 256.0f
#define SHIP_DEFAULT_RADIUS 16.0f

using namespace RGNDS;

Ship::Ship(olc::Sprite s)
	: GameObject()
	, SpaceObj(SHIP_DEFAULT_RADIUS)
	, currentShield(nullptr)
	, angRes(PI)
{ sprDissolve = s; }

Ship::~Ship() {
	clearUpgrades();
}

olc::Sprite* Ship::getSprite() { return &sprDissolve; }

void Ship::clearUpgrades() {
	currentShield = nullptr;

	for (ShipUpgrade* su : upgrades)
		delete su;

	for (ShipUpgrade* su : newUpgrades)
		delete su;

	upgrades.clear();
	newUpgrades.clear();
}

void Ship::addUpgrade(ShipUpgrade* upgrade) {

	if (upgrade->init())
		newUpgrades.push_back(upgrade);

	// If upgrade is instanceOf ShipUpgrade_Shield, the register as currentShield
	ShipUpgrade_Shield* shieldPtr = dynamic_cast<ShipUpgrade_Shield*>(upgrade);
	if (shieldPtr != nullptr)
		currentShield = shieldPtr;

	Debug("add ship upgrade " << upgrade);
}

bool Ship::shieldIsActive() { return currentShield;  }

Physics::Collision::Circle Ship::getCollider() {
	float radius = 14.0f;

	if (currentShield != nullptr)
		radius = currentShield->getRadius();

	return { pos.x, pos.y, radius * scale };
}

void Ship::onUpdate(float deltaTime) {

	if (currentShield) {
		auto list = Global::world->allShipShieldDeflectable();
		Physics::Collision c;
		for (auto go : list)
			if (Physics::Collision::checkCircleOnCircle(
				getCollider(),
				go->getColliders(),
				&c
			)) {
				Mix_PlayChannel(-1, Assets::shieldBump, 0);
				go->gotDeflected(this, currentShield, &c);
			}
	}

	// Add new Upgrades
	upgrades.insert(upgrades.end(), newUpgrades.begin(), newUpgrades.end());
	newUpgrades.clear();

	// Update upgrades
	ShipUpgrade* upgrade;
	for (int a = upgrades.size() - 1; a >= 0; a--) {
		upgrade = upgrades.at(a);
		if (!upgrade->update(this, deltaTime)) {
			if (upgrade == currentShield) {
				currentShield = nullptr;
			}
			Debug("remove ship upgrade " << upgrade);
			delete upgrade;

			upgrades.erase(upgrades.begin() + a);
		}
	}

	// Update Position based on physics
	olc::vf2d moveDirection = getDirection();
	float dot = moveDirection.x * dir.x + moveDirection.y * dir.y;

	// Update Position based on Screen-Borders
	updatePosition(deltaTime);
}

void Ship::drawUpgrades(olc::PixelGameEngine* pge, RGNDS::Transform* tr) {
	for (auto upgrade : upgrades)
		upgrade->draw(Global::game, *tr);
}
