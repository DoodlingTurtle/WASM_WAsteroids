#include "./textscene.h"

#include "../engine/Global.h"
#include "../engine/Assets.h"
using namespace RGNDS;

TextScene::TextScene(std::string assetFileName) 
{
    fileName      = assetFileName;
    text          = ""; 
    text_position = { 8, 9 };
}

TextScene::~TextScene() {}

void TextScene::onStart() { 
    text = Assets::loadText(fileName); 
    help_position = Global::layout->help_position;
    help_text     = "P = go back";
}
void TextScene::onEnd() { text = ""; help_text = ""; }

bool TextScene::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {
    if (Global::input.pressed & (KEYPAD_A))
        return false;
}

void TextScene::onDraw(olc::PixelGameEngine* pge) {
    pge->DrawStringDecal(text_position, text, olc::WHITE);
    pge->DrawString(help_position, help_text, olc::WHITE);
}

Scene* TextScene::nextScene() {
    return nullptr;
    //TODO: replace with propper content
}



