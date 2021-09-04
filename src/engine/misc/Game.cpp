#include "../Engine.h"

#include <cstdlib>
#include <ctime>

#include "../Global.h"
#include "../world/World.h"
#include "../Input.h"

namespace RGNDS {
	/*==============================================================================
	 * Game
	 *============================================================================*/

	Game::Game( Scene* startScene)
		:olc::PixelGameEngine(), currentScene(startScene), paused(false)
	{
		// Initialize functions
		srand(time(nullptr));
		Global::game = this;
		Global::world = new GameWorld();
		Global::input = new Input();

	}

	Game::~Game() {
		if (currentScene && !currentScene->persistent)
			delete currentScene;

		Global::game = nullptr;
		delete Global::world;
		delete Global::input;
	}

	void Game::pause() { paused = true; }
	void Game::resume() { paused = false; }

	bool Game::OnUserUpdate(float fElapsedTime) {

        Global::input->updateInputs(this);
		if (Global::input->exitCombo()) return false;
		
		if (currentScene != nullptr) {
			if (!paused) {
				Global::world->moveNew();
				for (auto go : Global::world->allUpdateable())
					go->onUpdate(fElapsedTime);
			}

			bool draw = currentScene->onUpdate(this, fElapsedTime);

			if (!paused){
				for (auto go : Global::world->findByAttribute(GameObject::DEAD))
					Global::world->removeGameObject(go);
			}

			// if the scene is activate after the logic update
			if (draw) {
				Clear(olc::BLANK);

				// Draw World
				for (auto go : Global::world->allDrawable())
					go->onDraw(this);

				// Draw Scene
				currentScene->onDraw(this);
			}
			else {
				// else switch to the next scene
				Scene* s = currentScene->nextScene();
				currentScene->onEnd();
				if (!currentScene->persistent)
					delete currentScene;

				currentScene = s;
				if (currentScene)
					currentScene->onStart(this);
				else
					return false;
			}

			// Remove Dead GOs
		}

		return true;
	}

}
