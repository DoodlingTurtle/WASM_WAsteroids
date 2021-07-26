#include "olcPixelGameEngine.h"
#include "config.h"
#include "scene.h"

#include "scenes/titlescreen.h"
#include "scenes/creditsscreen.h"
#include "scenes/maingame.h"

#include "gameobjects/asteroids.h"
#include <ctime>

#include "global.h"

//EMSCRIPTEN_KEEPALIVE int number = 0;

// Override base class with your custom functionality
class WAsteroids : public olc::PixelGameEngine
{
public:
    WAsteroids(){};
    ~WAsteroids(){};
    bool OnUserCreate() override {
        // Initialize functions
        srand(time(nullptr));
        currentScene = nullptr;
        
        //Generate starfield background
        starfield = new olc::Sprite(APP_SCREEN_WIDTH, APP_SCREEN_HEIGHT);
        for(int a = 0; a < CNT_STARS; a++) {
            uint8_t i = 96 + (rand()%64);
            starfield->SetPixel(
                    rand()%APP_SCREEN_WIDTH, 
                    rand()%APP_SCREEN_HEIGHT, 
                    olc::Pixel(i, i, i, 255)
            );
        }

        // Load first scene
        nextScene();

        //TODO: Override GetFontSprite() with own Font set

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override {

        Debug("update scene " << currentScene);
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
                Debug("Scene has ended");
                nextScene();
            }

        }

        return true;
    }

    void nextScene() {
        Debug("switch Scene:");
        Scene* next = nullptr;
        if(currentScene == nullptr)
            next = &titleScreen;
        else if(currentScene == (Scene*)&titleScreen) {
            switch(titleScreen.selectedMenu()) {
                case 2: { // Credits
                    next = &creditsScreen; break; }
                        
                case 0: { // new Game
                    Global::score = 0;                       //reset score
                    mainGameScreen.game_difficulty = 1.0f;   //reset difficulty
                    next = &mainGameScreen; 
                    break; }
                        
                case 1:
                default: {
                    next = &titleScreen; //TODO: add more Scenes (;.;)
                }
            }
        }
        else if(currentScene == (Scene*)&creditsScreen) {
            next = &titleScreen;
        }
        else if(currentScene == (Scene*)&mainGameScreen) {
            next = &titleScreen;
            //TODO: check for win condition then goto next level, or gameover
        }

        Debug("Asteroids spawned " << Global::asteroids);
        // Hook up global ressources and restart the new scene
        if(next != nullptr)
            next->restart();

        currentScene = next;
    }

    Scene*       currentScene;
    olc::Sprite* starfield;

    TitleScreen     titleScreen;
    CreditsScreen   creditsScreen;
    MainGameScreen  mainGameScreen;

};

int main()
{
//Setup global ressources
    Asteroids asteroids;

    Global::score = 0;
    Global::asteroids = &asteroids;

//Setup PGE 
    WAsteroids app;
    Global::pge = &app; 
    if (app.Construct(
        APP_SCREEN_WIDTH, 
        APP_SCREEN_HEIGHT, 
        APP_SCREEN_SCALE, 
        APP_SCREEN_SCALE
    )) app.Start();

    return 0;
}

