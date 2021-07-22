#ifndef COMPONENT_H
#define COMPONENT_H 1

#include "olcPixelGameEngine.h"
#include "asteroids.h"

class Scene {

public:
	Scene();
	virtual ~Scene();

    virtual void onStart();
	virtual	void onUpdate(olc::PixelGameEngine* pge, float deltaTime);
	virtual void onDraw(olc::PixelGameEngine* pge);
    virtual void onEnd();

	bool isActive();

    Asteroids* asteroids;

protected:
	void exit();

private:
	bool active;
};




#endif
