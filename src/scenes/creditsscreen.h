#ifndef __CreditsScreen_H__
#define __CreditsScreen_H__

#include "../olcPixelGameEngine.h"
#include "../scene.h"

class CreditsScreen: public Scene {
public:
    CreditsScreen();
    ~CreditsScreen();

    void onDraw(olc::PixelGameEngine*) override;
    void onUpdate(olc::PixelGameEngine*, float) override;

protected:
    void onStart() override;
    void onEnd() override;

private:
    olc::Sprite* spr;
};

#endif
