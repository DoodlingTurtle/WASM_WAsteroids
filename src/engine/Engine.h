#pragma once

#include "./olcPixelGameEngine.h"
#include "./Scene.h"

namespace RGNDS {

	class Game : public olc::PixelGameEngine {
	public:

		Game(Scene* startScene);
		~Game();

		virtual bool OnUserUpdate(float fElapsedTime) override;

		void pause();
		void resume();


	private:
		bool paused;
		Scene* currentScene;

	};

}
