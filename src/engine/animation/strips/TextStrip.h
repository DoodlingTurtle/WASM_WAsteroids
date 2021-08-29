#pragma once

#include "../Strip.h"
#include "../../SpriteSheet.h"
#include "../../Transform.h"

namespace RGNDS::Animation::Strips {

	class TextStrip : public RGNDS::Animation::Strip {
	public:
		TextStrip(std::string* text, bool textPersistent = false, bool persistent = false);
		~TextStrip();

		bool onTimelinePlay(float timeline, float playhead, float deltaTime) override;

		void onDraw(olc::PixelGameEngine* pge) override;

		Transform transform;

	private:
		bool textPersistent;
		std::string* text;
	};
}
