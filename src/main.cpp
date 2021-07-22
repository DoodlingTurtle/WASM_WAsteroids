#include "olcPixelGameEngine.h"
#include "config.h"
#include "scene.h"
#include "scenes/titlescreen.h"

#include "asteroids.h"

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
		currentScene = nextScene();

        //TODO: Override GetFontSprite() with own Font set

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {

		if(currentScene != nullptr) {
			currentScene->onUpdate(this, fElapsedTime);
			if(currentScene->isActive()) {
                Clear(olc::BLACK);
                SetPixelMode(olc::Pixel::ALPHA); 
				currentScene->onDraw(this);
                SetPixelMode(olc::Pixel::NORMAL); 
			}
			else {
				printf("Scene has ended\n");
				currentScene = nextScene();
			}

		}

		// Called once per frame, draws random coloured pixels
		return true;
	}

	Scene* nextScene() {
        Scene* next = nullptr;
        if(currentScene == nullptr)
            next = &titleScreen;
        else if(currentScene == (Scene*)&titleScreen)
			next = &titleScreen; //TODO: add more Scenes (;.;)
        
        if(currentScene != nullptr){
            printf("currentScene: %d\n", currentScene);
            currentScene->onEnd();
        }

        if(next != nullptr) {
            next->asteroids = &asteroids;
            next->onStart();
        }

        return next;
	}

	Asteroids   asteroids;
	TitleScreen titleScreen;
	Scene*      currentScene;

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

