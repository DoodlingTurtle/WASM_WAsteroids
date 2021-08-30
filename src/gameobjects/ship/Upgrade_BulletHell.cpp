#include "./Upgrade_BulletHell.h"
#include "../../engine/Macros.h"
#include "../../engine/Global.h"

/*==============================================================================
 * UpgradeBulletHell
 *============================================================================*/

int UpgradeBulletHell::instances = 0;

UpgradeBulletHell::UpgradeBulletHell() { instances++; }
UpgradeBulletHell::~UpgradeBulletHell() { instances--; }

bool UpgradeBulletHell::invokeShipComponent(ShipStats* stats, Ship* ship) {

	float steps = 16;

	float ang = 0;
	float step = PI2 / steps;
	float dist = 24.0f;

	olc::vf2d dir;

	for (int a = 0; a < steps; a++) {

		dir.x = cos(ang);
		dir.y = sin(ang);

		Bullet* b = stats->prototypeBullet->clone((dir * dist) + ship->pos, dir, 0.0f);

		Global::world->addGameObject(b);

		ang += step;
	}

	return false;
}

bool UpgradeBulletHell::updateShipComponent(float deltaTime) { draw = true;  return true; }

bool UpgradeBulletHell::drawShipComponent(ShipStats* stats, Ship* ship, olc::PixelGameEngine* pge, olc::vf2d componentListIconCoordinates) {

	if (draw) {
		pge->DrawStringDecal(componentListIconCoordinates, "Bullet Hell (" + std::to_string(instances) + "x)");
		draw = false;
		return true;
	}

	return false;
}
