#pragma once
#include "../../olcPixelGameEngine.h"

namespace RGNDS::World {
	class Drawable {
	public:
		virtual void onDraw(olc::PixelGameEngine*) = 0;
	};
}
