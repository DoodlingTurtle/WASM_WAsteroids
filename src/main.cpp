#include "olcPixelGameEngine.h"
#include "config.h"
#include "scene.h"
#include "particles.h"

#include "scenes/titlescreen.h"
#include "scenes/creditsscreen.h"
#include "scenes/maingame.h"
#include "scenes/pausescreen.h"

#include "gameobjects/asteroids.h"
#include "particles/asteroid_particles.h"

#include "gameobjects/ship/shipstats.h"

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
        
        // setup layers
        layer_blackout = CreateLayer();
        layer_ship  = CreateLayer();
        layer_asteroids = CreateLayer();
        layer_shots = CreateLayer();
        layer_stars= CreateLayer();

        // initialize Layers
        SetDrawTarget(layer_stars);
        Clear(olc::BLANK);
        for(int a = 0; a < CNT_STARS; a++) {
            uint8_t i = 96 + (rand()%64);
            Draw(
                    rand()%APP_SCREEN_WIDTH, 
                    rand()%APP_SCREEN_HEIGHT, 
                    olc::Pixel(i, i, i, 255)
            );
        }
        EnableLayer(layer_stars, true);

        SetDrawTarget(layer_shots);
        Clear(olc::BLANK);
        EnableLayer(layer_shots, true);

        SetDrawTarget(layer_asteroids);
        Clear(olc::BLANK);
        EnableLayer(layer_asteroids, true);

        SetDrawTarget(layer_ship);
        Clear(olc::BLANK);
        EnableLayer(layer_ship, true);

        SetDrawTarget(layer_blackout);
        SetPixelMode(olc::Pixel::ALPHA);
        Clear((olc::Pixel){0, 0, 0, 128});
        SetPixelMode(olc::Pixel::NORMAL);

        SetDrawTarget(nullptr);

        // Define Particles
        Asteroid_Particle::init(this);


        // Load first scene
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
                Clear(olc::BLANK);
                currentScene->onDraw(this);
            }
            else {
                // else switch to the next scene
                Debug("Scene has ended");
                nextScene();
            }

        }

        return true;
    }

    bool OnUserDestroy() override {
        Asteroid_Particle::deinit();
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
                    Global::shipStats->resetToLV1();
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
            switch(mainGameScreen.getState()) {
                case MainGameScreen::STATE_WON:
                    mainGameScreen.game_difficulty+=0.66f;
                    next = &mainGameScreen;
                    break;

                case MainGameScreen::STATE_RUNNING:
                    next = &pauseScreen;
                    break;

                case MainGameScreen::STATE_LOST: 
                    //TODO: add GameOver-Screen
                default:
                    next = &titleScreen; 
                    break;

            }
        }
        else if(currentScene == (Scene*)&pauseScreen) {
            if(pauseScreen.endGame()) {
                mainGameScreen.reset();
                next = &titleScreen;
            } else 
                next = &mainGameScreen;
        }

        // Hook up global ressources and restart the new scene
        if(next != nullptr)
            next->restart();

        currentScene = next;
    }

    Scene*       currentScene;

    TitleScreen     titleScreen;
    CreditsScreen   creditsScreen;
    MainGameScreen  mainGameScreen;
    PauseScreen     pauseScreen = PauseScreen(&mainGameScreen);

};

int main()
{
//Setup global ressources
    Asteroids       asteroids;
    ShipStats       shipStats;

    Global::score = 0;
    Global::asteroids = &asteroids;
    Global::shipStats = &shipStats;

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

