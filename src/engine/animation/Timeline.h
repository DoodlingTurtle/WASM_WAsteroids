#pragma once

#include "../world/components/Updateable.h"

namespace RGNDS {
	namespace Animation {

		class Strip;

		/**
		 * Allows you to define a sequence of Event, dependent on Time passed
		 */
		class Timeline : public World::Updateable {
		public:
			Timeline();
			virtual ~Timeline();

			/**
			 * Puts a new Event onto the Timeline.
			 * \param strip		
			 * \param startTime - time relative from the timeline start
			 *                    from which the event becomes active (in seconds)
			 * \param loops	    - After the event has ended, it will be repeated until loops becomes 0
			 *                    each iteration causes loop to reduce by 1 (put -1 in for inifinite loops)
			 */
			void addStrip(Strip* strip, float startTime, int loops);

			/**
			 * Must be called once per cycle, to play the timeline.
			 * \param deltaTime - how much time has passed since the last update call (in 1/1000th of a second)
			 */
			void onUpdate(float deltaTime);

			void onDraw(olc::PixelGameEngine* pge);

		protected:
			float playHead;
			int slotSize;

		private:
			struct MetaStrip {
				Strip* s;
				float t;
				int l;
			};

			std::unordered_map<int, std::vector<MetaStrip>> invisibleStrips;
			std::vector<MetaStrip> playingStrips;
		};
	};
};
