#pragma once

#include "../engine/Scene.h"

using namespace RGNDS;

class LoadScreen : public Scene {
public:
    LoadScreen();
    virtual~LoadScreen();

	bool onUpdate(olc::PixelGameEngine* pge, float deltaTime) override;
	void onDraw(olc::PixelGameEngine* pge) override;

    Scene* nextScene() override;

protected:
    void onEnd() override;
    std::string msg;

};
