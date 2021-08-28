#include "../Engine.h"

#include <cstdlib>
#include <ctime>

#include "../Global.h"

namespace RGNDS {
	/*==============================================================================
	 * Game
	 *============================================================================*/

	Game::Game()
		: olc::PixelGameEngine(), currentScene(nullptr)
	{
		// Initialize functions
		srand(time(nullptr));

		paused = false;
	}

	Game::~Game() {
		if (currentScene && !currentScene->persistent)
			delete currentScene;
	}

	void Game::pause() { paused = true; }
	void Game::resume() { paused = false; }

	bool Game::OnUserCreate() { return true; }
	bool Game::OnUserUpdate(float fElapsedTime) {

        Global::input.updateInputs();

		if (currentScene != nullptr) {

			if(!paused) {
				Global::world.moveNew();

				for (auto go : Global::world.allUpdateable())
					go->onUpdate(fElapsedTime);

				// Remove Dead GOs
				for (auto go : Global::world.findByAttribute(GameObject::DEAD))
					Global::world.removeGameObject(go);
			}

			// if the scene is activate after the logic update
			if (currentScene->onUpdate(this, fElapsedTime)) {
				Clear(olc::BLANK);

				// Draw World
				for (auto go : Global::world.allDrawable())
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
					currentScene->onStart();
				else
					return false;
			}

		}

		return true;
	}


}
