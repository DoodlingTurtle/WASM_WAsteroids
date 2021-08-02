#ifndef COMPONENT_H
#define COMPONENT_H 1

#include "olcPixelGameEngine.h"
#include "gameobjects/asteroids.h"

class Scene {

public:
	Scene();
	virtual ~Scene();

    void restart();

	virtual	void onUpdate(olc::PixelGameEngine* pge, float deltaTime);
	virtual void onDraw(olc::PixelGameEngine* pge);


	bool isActive();

    Asteroids* asteroids;

protected:
    virtual void onStart();
    virtual void onEnd();
    
	void exit();

private:
	bool active;
};




#endif
