#pragma once

#include "./olcPixelGameEngine.h"

namespace RGNDS {

	class Game;

	class Scene {

	public:
		Scene( bool persistent = false );
		virtual ~Scene();

		virtual	bool onUpdate(olc::PixelGameEngine* pge, float deltaTime);
		virtual void onDraw(olc::PixelGameEngine* pge);

		virtual Scene* nextScene() = 0;

		virtual void onStart();
		virtual void onEnd();

	protected:
		bool persistent;

	private:

		friend class Game;

	};

}
