#include "Strip.h"
#include "Timeline.h"

namespace RGNDS::Animation {

	/*==============================================================================
	 * Strip
	 *============================================================================*/
	Strip::Strip(bool persistent) : persistent(persistent) { }
	void Strip::onDraw(olc::PixelGameEngine* pge) {}

	/*==============================================================================
	 * Timeline
	 *============================================================================*/
	Timeline::Timeline() :playHead(0.0f), slotSize(100) { };
	Timeline::~Timeline() {
		for (auto s : playingStrips)
			if (!s.s->persistent)
				delete s.s;

		playingStrips.clear();

		for (auto it : this->invisibleStrips) {
			for (auto s : it.second)
				if (!s.s->persistent)
					delete s.s;

			it.second.clear();
		}
		this->invisibleStrips.clear();
	};

	void Timeline::addStrip(Strip* strip, float startTime, int loops) {
		int slot = startTime / slotSize;

		auto it = invisibleStrips.find(slot);
		if (it == invisibleStrips.end()) {
			invisibleStrips.emplace(slot, std::vector<MetaStrip>());
			it = invisibleStrips.find(slot);
		}

		it->second.push_back(MetaStrip{ strip, startTime, loops });
	}

	void Timeline::onUpdate(float dt) {
		playHead += dt;
		int slot = playHead / slotSize;
		auto it = invisibleStrips.find(slot);

		//DONE: add all invisibleStrips if the there startTime has been reached
		if (it != invisibleStrips.end()) {
			for (int a = it->second.size() - 1; a >= 0; a--) {
				auto strip = it->second.at(a);
				if (strip.t <= playHead) {
					playingStrips.push_back(strip);
					it->second.erase(it->second.begin() + a);
				}
			}
		}

		//DONE: Update All visible strips
		for (auto strip = playingStrips.begin(); strip != playingStrips.end(); ) {
			if (strip->s->onTimelinePlay(playHead, playHead - strip->t, dt)) {
				strip++;
			}
			else if (strip->l > 0 || strip->l == -1) {
				strip->t = playHead;
				if (strip->l > 0) strip->l--;
				strip++;
			}
			else {
				if (!strip->s->persistent)
					delete strip->s;
				strip = playingStrips.erase(strip);
			}
		}
	}

	void Timeline::onDraw(olc::PixelGameEngine* pge) {
		for (auto strip : playingStrips)
			strip.s->onDraw(pge);
	}
}

