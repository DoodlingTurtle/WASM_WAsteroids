#include "./olcPixelGameEngine.h"
#include <SDL/SDL_mixer.h>

#include "gameinput.h"
#include "particles.h"

#include "scene.h"
#include "scenes/loadscreen.h"
#include "scenes/titlescreen.h"
#include "scenes/maingame.h"
#include "scenes/pausescreen.h"
#include "scenes/upgradescreen.h"
#include "scenes/gameoverscreen.h"
#include "scenes/textscene.h"
#include "scenes/soundtest.h"
//#include "scenes/helpscreen.h"
//#include "scenes/creditsscreen.h"

#include "gameobjects/asteroids.h"
#include "gameobjects/ship/shipupgrade_shield.h"

#include "gameobjects/ship/shipstats.h"

#include <cstdlib>
#include <ctime>

#include "config.h"
#include "assets.h"
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
        auto _setupLayer = [this](bool en=true, std::function<void()> fnc = [](){}){
            int ret = CreateLayer();
            SetDrawTarget(ret);
            Clear(olc::BLANK);
            fnc();
            EnableLayer(ret, en);
            return ret;
        };

        layer_blackout = _setupLayer(false, [this](){
            SetPixelMode(olc::Pixel::ALPHA);
            Clear(olc::Pixel{0, 0, 0, 128});
            SetPixelMode(olc::Pixel::NORMAL);
        });

        layer_ship      = _setupLayer();
        layer_asteroids = _setupLayer();
        layer_shots     = _setupLayer();
        layer_particles = _setupLayer();
        layer_stars     = _setupLayer(true, [this](){
            for(int a = 0; a < CNT_STARS; a++) {
                uint8_t i = 96 + (rand()%64);
                Draw(
                    rand()%Global::layout->app_width, 
                    rand()%Global::layout->app_height, 
                    olc::Pixel(i, i, i, 255)
                );
            }
        });


        SetDrawTarget(nullptr);

        // Load first scene
        nextScene();
        
        //TODO: Override GetFontSprite() with own Font set

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override {
        Global::gameInput->updateInputs();

        if(currentScene != nullptr) {
        // Update logic
            currentScene->onUpdate(this, fElapsedTime);
            
        // if the scene is activate after the logic update
            if(currentScene->isActive()) {
                // draw a new frame
                SetDrawTarget(layer_particles);
                    Clear(olc::BLANK);
                SetDrawTarget(nullptr);
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
        //Stop all SFX from playing
        Mix_HaltChannel(-1);

        // Destroy loaded graphics
        ShipUpgrade_Shield::deinit();

        Assets::deinit();
        return true;
    }

    void nextScene() {
        Debug("switch Scene:");
        Scene* next = nullptr;
        if(currentScene == nullptr)
            next = &loadScreen;
        else if(currentScene == (Scene*)&loadScreen) {
            Debug("prev = loadScreen");
            next = &titleScreen; 
        }
       
        else if(currentScene == (Scene*)&titleScreen) {
            Debug("prev = titleScreen");
            switch(titleScreen.selectedMenu()) {
                case 2: { // Credits
                    next = &creditsScreen; break; }
                        
                case 0: { // new Game
                    Global::score = 0;                       //reset score
                    mainGameScreen.reset();
                    Global::shipStats->resetToLV1();
                    next = &mainGameScreen; 
                    break; }
                     
                case 1: { // help
                    next = &helpScreen; break; }
                        
                case 3: {  /*Soundtest*/ next = &soundTest; break; }
                default: {
                    next = &titleScreen;
                }
            }
        }
        else if(
                currentScene == (Scene*)&gameOverScreen || 
                currentScene == (Scene*)&creditsScreen ||
                currentScene == (Scene*)&helpScreen
        ) { 
            next = &titleScreen; 
        }
        else if(currentScene == (Scene*)&mainGameScreen) {
            Debug("prev = mainGameScreen");
            switch(mainGameScreen.getState()) {
                case MainGameScreen::STATE_WON: next = &upgradeScreen; break;
                case MainGameScreen::STATE_RUNNING: next = &pauseScreen; break;
                case MainGameScreen::STATE_LOST: next = &gameOverScreen; break;

                default: next = &titleScreen; break;

            }
        }
        else if(currentScene == (Scene*)&pauseScreen) {
            Debug("prev = pauseScreen");
            if(pauseScreen.endGame()) {
                mainGameScreen.reset();
                next = &titleScreen;
#ifdef DEBUG_BUILD
            } else if(pauseScreen.skipLevel()) {
                 mainGameScreen.endLevel();
                 next = &upgradeScreen;
#endif
            } else {
                next = &mainGameScreen;
            }
        }
        else if(currentScene == (Scene*)&upgradeScreen) {
            Debug("prev = upgradeScreen");
            mainGameScreen.game_difficulty+=0.66f;
            Global::asteroids->killall();
            next = &mainGameScreen;
        }

        // Hook up global ressources and restart the new scene
        if(next != nullptr)
            next->restart();

        

        currentScene = next;
    }

    Scene*          currentScene;

    TitleScreen     titleScreen;
    
    TextScene       creditsScreen = TextScene("credits.txt");
    TextScene       helpScreen    = TextScene("help.txt");
    MainGameScreen  mainGameScreen;
    PauseScreen     pauseScreen   = PauseScreen(&mainGameScreen);
    UpgradeScreen   upgradeScreen = UpgradeScreen(
            Global::shipStats, &Global::score, 
            &mainGameScreen.game_difficulty);
    GameOverScreen  gameOverScreen;
    SoundTest       soundTest;
    LoadScreen      loadScreen;

};

int main()
{
    Debug("main");

// Setup SDL_Mixer
    bool run = true;
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        Debug("failed to init audio device");
        run = false;
    }

    if(run) {
    //Setup global ressources
    // layout has to be set, in very first play, otherwise everything else explodes
    // TODO: store and get layout via Browser localStorage
        int screenLayout = 0;    
        Global::layout = &screenLayouts[screenLayout];

        Asteroids       asteroids;
        ShipStats       shipStats;
    
        Global::score = 0;
        Global::asteroids = &asteroids;
        Global::shipStats = &shipStats;
    
        WAsteroids      app;

    // Setup GameInput
        GameInput           gameInput(&app);
        Global::gameInput = &gameInput;

    //Setup PGE 
        Global::pge = &app; 
        if (run && app.Construct(
            Global::layout->app_width,
            Global::layout->app_height,
            Global::layout->app_scale,
            Global::layout->app_scale
        )) app.Start();

        Global::switchBGMusic(nullptr);

    // Close SDL_Mixer
        Mix_CloseAudio();
        Mix_Quit();
    }

    return 0;
}

