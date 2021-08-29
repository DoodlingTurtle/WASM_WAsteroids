#pragma once

#include "../Strip.h"
#include "../../SpriteSheet.h"
#include "../../Transform.h"

namespace RGNDS::Animation::Strips {

	class SpriteSheetStrip : public RGNDS::Animation::Strip {
	public:
		SpriteSheetStrip(SpriteSheet* sheet, bool spritePersistent=false, bool persistent=false);
		~SpriteSheetStrip();

		bool onTimelinePlay(float timeline, float playhead, float deltaTime) override;

		void onDraw(olc::PixelGameEngine* pge) override;

		Transform transform;

	private:
		bool spritePersistent;
		SpriteSheet* spriteSheet;


	};

}
