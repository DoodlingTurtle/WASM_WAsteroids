#include "../SpriteSheet.h"

#include <math.h>

namespace RGNDS {
	
	SpriteSheet::SpriteSheet()
		: currentFrame(0), spriteSize({0, 0}), tilesPerRow(0)
		, defaultFPS(1/30.0f), tint(olc::WHITE)
		, lerpFrame(&currentFrame)
		, lerpTint(&tint)
	{ }
	SpriteSheet::~SpriteSheet() {}


	bool SpriteSheet::setup(const olc::vi2d& spriteSize, float fps) {
		defaultFPS = 1 / fps;

		olc::Sprite* spr = Sprite();

		if (spriteSize.x > spr->width || spriteSize.y > spr->height) {
			return false;
		}

		tilesPerRow = std::floor(spr->width / spriteSize.x);
		this->spriteSize = spriteSize;

		return true;
	}

	void SpriteSheet::onUpdate(float dt) {
		if (playlist.begin() != playlist.end()) {
			lerpFrame.update(dt);

			if (lerpFrame.finished()) {
				auto q = playlist.begin();
				if (!q->lo || playlist.size() > 1)
					q = playlist.erase(q);
			
				
				if (q != playlist.end())
					setupFrameLerp(*q);
			}
		}

		lerpTint.update(dt);
	}

	void SpriteSheet::setFrame(int frm) {
		playlist.clear();
		currentFrame = frm;
	}

	void SpriteSheet::playRange(int first, int last, bool loop, float time) {
		if (time < 0) 
			time = (float)(last - first + 1) * defaultFPS;

		playlist.clear();
		playlist.push_back({ first, last, time, loop });
		setupFrameLerp(*playlist.begin());
	}

	void SpriteSheet::queueRange(int first, int last, bool loop, float time) {
		bool setLerp = (playlist.size() == 0);

		if (time < 0) 
			time = (float)(last - first + 1) * defaultFPS;

		playlist.push_back({ first, last, time, loop });
		if(setLerp) setupFrameLerp(*playlist.begin());
	}

	void SpriteSheet::drawDecal(
		olc::PixelGameEngine* pge,
		const olc::vf2d& pos, const olc::vf2d& scale,
		const float fAngle, const olc::vf2d& center
	) {
		if (tilesPerRow == 0) return;

		olc::vi2d p;
		p.x = (float)(currentFrame % tilesPerRow);
		p.y = (currentFrame - p.x) / tilesPerRow;

		p *= spriteSize;
		pge->DrawPartialRotatedDecal(pos, this->Decal(), fAngle, center, p, spriteSize, scale, tint);
	}

	void SpriteSheet::changeTint(const olc::Pixel& p, float seconds) {
		lerpTint.changeTarget(p, seconds);
	}

	void SpriteSheet::setupFrameLerp(const anim_queue& q) {
		currentFrame = q.f;
		lerpFrame.changeTarget(q.l, q.s);
	}

};