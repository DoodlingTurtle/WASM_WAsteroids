#pragma once

#include "../ship.h"
#include "../../gamecomponents.h"

class Saucer 
	: public Ship 
	, public PlayerHitable
{
public:
	Saucer();
	~Saucer();

	void onDraw(olc::PixelGameEngine* pge) override;
	void onUpdate(float deltatime) override;
	
	// Inherited via BulletHitable
	virtual std::vector<Physics::Collision::Circle> getColliders() override;
	virtual void hitByBullet(Bullet*, Physics::Collision*) override;
	virtual int getDestructionScore() override;

private:
	float deltaTimeAccumu;
	float fireRateDeltaTime;


};
