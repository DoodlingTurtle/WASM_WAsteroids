#pragma once

#include <unordered_map>
#include "./ship_component.h"

class MultiUseUpgrade : public ShipComponent{
public:
	MultiUseUpgrade(const int);
	~MultiUseUpgrade();
	
	// Inherited via ShipComponent
	bool updateShipComponent(float deltaTime) override;

protected:
	int getInstances();
	bool allowDraw();

	static std::unordered_map<int, int> instances;
	static std::unordered_map<int, bool> draw;

private:
	int id;

};
