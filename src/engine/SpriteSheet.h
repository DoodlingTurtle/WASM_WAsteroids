#pragma once

#include <vector>
#include "./olcPixelGameEngine.h"
#include "./Lerp.h"

namespace RGNDS {
	class SpriteSheet : public olc::Renderable {
	public:
		SpriteSheet();
		~SpriteSheet();

		bool setup(const olc::vi2d& spriteSize, float defaultFPS=30.0f);

		void onUpdate(float fDeltaTime);

		void drawDecal(
			olc::PixelGameEngine* pge, 
			const olc::vf2d& pos = { 0.0f, 0.0f },
			const olc::vf2d& scale = { 1.0f, 1.0f },
			const float fAngle = 0.0f, 
			const olc::vf2d& center = { 0.0f, 0.0f }
		);
	
		void setFrame(int frame);
		void playRange(int firstFrame, int lastFrame, bool loop = false, float seconds=-1);
		void queueRange(int firstFrame, int lastFrame, bool loop = false, float seconds=-1);

		void changeTint(const olc::Pixel&, float seconds = 0.0f);

	private:

		struct anim_queue{
			int f, l;
			float s;
			bool lo;
		};

		void setupFrameLerp(const anim_queue& queue);

		int				 tilesPerRow;
		olc::vf2d		 spriteSize;
		float            defaultFPS;

		int				 currentFrame;
		Lerp<int>		 lerpFrame;

		olc::Pixel		 tint;
		Lerp<olc::Pixel> lerpTint;

		std::vector<anim_queue> playlist;
		
	};
};
