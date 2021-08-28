#pragma once

#include "../olcPixelGameEngine.h"

namespace RGNDS {
	namespace Animation {

		class Timeline;

		class Strip {
		public:
			/**
			 * Constructor.
			 * 
			 * \param persistent - defines, if the Timeline is allowed to delete this instance by itself.
			 *                     (if it is false, the Timeline will only remove the pointer, but not the instance)
			 */
			Strip(bool persistent=false);

			/**
			 * Called on every timeline update (once the Strip has started playing).
			 * 
			 * \param totalPlaytime    - the current position of the playhead in the timeline
			 * \param relativePlaytime - the time passed, since this strip has started playing
			 *
			 * \return - true = the Timeline will keep the strip and continues to update it
			 *           false = the Timeline will remove (and delete if persistent==false) the Strip from the timeline
			 *           If there Strip has been set to loop, this instance is reset and played again
			 */
			virtual bool onTimelinePlay(float totalPlaytime, float relativePlaytime) = 0;


			virtual void onDraw(olc::PixelGameEngine* pge);

		private:
			bool persistent;

			friend class Timeline;
		};

	}
}
