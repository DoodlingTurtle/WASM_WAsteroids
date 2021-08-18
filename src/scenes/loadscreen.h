#ifndef __LoadScreen_H__
#define __LoadScreen_H__

#include "../scene.h"

class LoadScreen : public Scene {
public:
    LoadScreen();
    virtual~LoadScreen();

	void onUpdate(olc::PixelGameEngine* pge, float deltaTime) override;
	void onDraw(olc::PixelGameEngine* pge) override;

protected:
    void onEnd() override;
    std::string msg;

};

#endif
