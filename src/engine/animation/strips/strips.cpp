#include "../Strip.h"
#include "./SpriteSheetStrip.h"
#include "./TextStrip.h"

namespace RGNDS::Animation::Strips {
	/*==============================================================================
	 * SpriteSheetStrip
	 *============================================================================*/
	SpriteSheetStrip::SpriteSheetStrip(SpriteSheet* sheet, bool spritePersistent, bool persistent)
		: RGNDS::Animation::Strip(persistent)
		, spriteSheet(sheet), spritePersistent(spritePersistent)
	{}
	SpriteSheetStrip::~SpriteSheetStrip() {
		if (!spritePersistent)
			delete spriteSheet;
	}

	void SpriteSheetStrip::onDraw(olc::PixelGameEngine* pge) {
		spriteSheet->drawDecal(pge, transform.pos,
			{ transform.scale, transform.scale },
			transform.ang, transform.origin
		);
	}

	bool SpriteSheetStrip::onTimelinePlay(float timeline, float playhead, float deltaTime) { return true; }


	/*==============================================================================
	 * TextStrip
	 *============================================================================*/
	TextStrip::TextStrip(std::string* text, bool textPersistent, bool persistent)
		: RGNDS::Animation::Strip(persistent), text(text), textPersistent(textPersistent)
	{ }
	TextStrip::~TextStrip() { if (!textPersistent) delete text; }

	void TextStrip::onDraw(olc::PixelGameEngine* pge) { pge->DrawStringDecal(transform.pos, *text, olc::WHITE); }
	bool TextStrip::onTimelinePlay(float timeline, float playhead, float deltaTime) { return true; }

}
