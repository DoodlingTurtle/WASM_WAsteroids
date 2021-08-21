#include "./textscene.h"

#include "global.h"
#include "assets.h"

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

void TextScene::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {
    if(Global::gameInput->pressed&(KEYPAD_A))
        exit();
}

void TextScene::onDraw(olc::PixelGameEngine* pge) {
    pge->DrawStringDecal(text_position, text, olc::WHITE);
    pge->DrawString(help_position, help_text, olc::WHITE);
}
