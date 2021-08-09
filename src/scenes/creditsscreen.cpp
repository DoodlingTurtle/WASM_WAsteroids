#include "creditsscreen.h"
#include "stdio.h"

CreditsScreen::CreditsScreen() {
    lines = std::vector<std::string>();
    
}
CreditsScreen::~CreditsScreen() {}

void CreditsScreen::onStart() {
    FILE* text = fopen("./assets/credits.txt", "rb");

    if(text) while( !feof(text) ) {
        char buffer[1024]{ 0 };
        fgets(buffer, 1024, text);
        std::string str(buffer);

        lines.push_back(str);
    }
    fclose(text);

}
void CreditsScreen::onEnd() {
    lines.clear();
}

void CreditsScreen::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {
    if(   pge->GetKey(olc::ENTER).bPressed
       || pge->GetKey(GameKeyMap[KEYPAD_A]).bPressed
    ) exit();
}

void CreditsScreen::onDraw(olc::PixelGameEngine* pge) {
    float y = 9;
    for(std::string s : lines) {
        pge->DrawStringDecal({
            8, y
        }, s, olc::WHITE);

        y += 10;
    }
}
