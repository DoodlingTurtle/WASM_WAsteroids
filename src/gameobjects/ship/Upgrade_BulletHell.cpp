#include "./Upgrade_BulletHell.h"
#include "../../engine/Macros.h"
#include "../../engine/Global.h"

/*==============================================================================
 * UpgradeBulletHell
 *============================================================================*/
UpgradeBulletHell::UpgradeBulletHell() : MultiUseUpgrade(1) {}

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

	stats->generator = 0.0f;

	return false;
}

bool UpgradeBulletHell::drawShipComponent(ShipStats* stats, Ship* ship, olc::PixelGameEngine* pge, olc::vf2d componentListIconCoordinates) {
	if (allowDraw()) {
		pge->DrawStringDecal(componentListIconCoordinates, "Bullet Hell (" + std::to_string(getInstances()) + "x)");
		return true;
	}
	else return false;
}

