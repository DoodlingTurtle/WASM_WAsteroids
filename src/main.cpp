#include "olcPixelGameEngine.h"
#include "config.h"
#include "scene.h"
#include "scenes/titlescreen.h"
#include "scenes/creditsscreen.h"

#include "gameobjects/asteroids.h"

#include <ctime>
#include <stdio.h>
using namespace std;

//EMSCRIPTEN_KEEPALIVE int number = 0;

// Override base class with your custom functionality
class WAsteroids : public olc::PixelGameEngine
{
public:
    bool OnUserCreate() override {
        srand(time(nullptr));
        asteroids.init(this);
        currentScene = nullptr;

        starfield = new olc::Sprite(APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT);
        for(int a = 0; a < CNT_STARS; a++) {
            uint8_t i = 96 + (rand()%64);
            starfield->SetPixel(
                    rand()%APP_SCREEN_WIDTH, 
                    rand()%APP_SCREEN_HEIGHT, 
                    olc::Pixel(i, i, i, 255)
            );
        }

        nextScene();

        //TODO: Override GetFontSprite() with own Font set

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override {

        if(currentScene != nullptr) {
        // Update logic
            currentScene->onUpdate(this, fElapsedTime);
            
        // if the scene is activate after the logic update
            if(currentScene->isActive()) {
                // draw a new frame
                DrawSprite(0, 0, starfield);
                SetPixelMode(olc::Pixel::ALPHA); 
                currentScene->onDraw(this);
                SetPixelMode(olc::Pixel::NORMAL); 
            }
            else {
                // else switch to the next scene
                printf("Scene has ended\n");
                nextScene();
            }

        }

        return true;
    }

    void nextScene() {
        Scene* next = nullptr;
        if(currentScene == nullptr)
            next = &titleScreen;
        else if(currentScene == (Scene*)&titleScreen) {
            printf("Selected: %d\n", titleScreen.selectedMenu());
            switch(titleScreen.selectedMenu()) {
                case 2: { // Credits
                    next = &creditsScreen; 
                    break;
                }
                case 0:
                case 1:
                default: {
                    next = &titleScreen; //TODO: add more Scenes (;.;)
                }
            }
        }
        else if(currentScene == (Scene*)&creditsScreen) {
            next = &titleScreen;
        }

        // Hook up global ressources and restart the new scene
        if(next != nullptr) {
            next->asteroids = &asteroids;
            next->restart();
        }

        currentScene = next;
    }

    Asteroids   asteroids;
    Scene*      currentScene;
    olc::Sprite* starfield;

    TitleScreen titleScreen;
    CreditsScreen creditsScreen;
};

int main()
{
    WAsteroids app;

    if (app.Construct(
        APP_SCREEN_WIDTH, 
        APP_SCREEN_HEIGHT, 
        APP_SCREEN_SCALE, 
        APP_SCREEN_SCALE
    )) app.Start();

    return 0;
}

