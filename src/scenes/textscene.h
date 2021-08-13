#ifndef __TextScene_H__
#define __TextScene_H__

#include <string>

#include "../olcPixelGameEngine.h"
#include "../scene.h"

class TextScene: public Scene {
public:
    TextScene(std::string assetFileName);
    ~TextScene();

    void onDraw(olc::PixelGameEngine*) override;
    void onUpdate(olc::PixelGameEngine*, float) override;

protected:
    void onStart() override;
    void onEnd() override;

private:
    olc::vf2d   text_position;
    std::string text;
    std::string fileName;
    
    std::string help_text;
    olc::vf2d   help_position;
};

#endif
