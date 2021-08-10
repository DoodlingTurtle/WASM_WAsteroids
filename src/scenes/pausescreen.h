#ifndef __PauseScreen_H__
#define __PauseScreen_H__

#include "../olcPixelGameEngine.h"
#include "../scene.h"
#include "../textmenu.h"

class PauseScreen : public Scene {
public:
    PauseScreen(Scene* backgroundProvider);
    virtual~PauseScreen();

    void onUpdate(olc::PixelGameEngine* pge, float deltaTime) override;
    void onDraw(olc::PixelGameEngine* pge) override;
    void onStart() override;
    void onEnd() override;

#ifdef DEBUG_BUILD
    bool skipLevel();
#endif

    bool endGame();

protected:
    Scene* backgroundProvider;

private:
    TextMenu menu;

};

#endif
