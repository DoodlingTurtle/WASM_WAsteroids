#include "./MultiUseUpgrade.h"

/*==============================================================================
 * LimitUserUpgrade
 *============================================================================*/

std::unordered_map<int, bool> MultiUseUpgrade::draw = std::unordered_map<int, bool>();
std::unordered_map<int, int>  MultiUseUpgrade::instances = std::unordered_map<int, int>();

MultiUseUpgrade::MultiUseUpgrade(const int id) : id(id) {
	if (instances.find(id) == instances.end())
		instances.emplace(id, 0);

	instances[id]++;

	if (draw.find(id) == draw.end())
		draw.emplace(id, true);
}

MultiUseUpgrade::~MultiUseUpgrade() {
	instances[id]--;
}

bool MultiUseUpgrade::updateShipComponent(float deltaTime) {
	draw[id] = true;
	return true;
}

int MultiUseUpgrade::getInstances() { return instances[id]; }

bool MultiUseUpgrade::allowDraw() {
	bool ret = draw[id];
	draw[id] = false;
	return ret;
}

