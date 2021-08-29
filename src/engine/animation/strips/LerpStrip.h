#pragma once

#include "../../Lerp.h"
#include "../Strip.h"

namespace RGNDS::Animation::Strips {

	template<typename T>
	class LerpStrip : public RGNDS::Animation::Strip, public RGNDS::Lerp<T> {
	public:
		LerpStrip(T* target) : RGNDS::Lerp<T>(target) {}

		bool onTimelinePlay(float totalPlaytime, float playHead, float dt) override {
			Lerp<T>::playHead = playHead;
			if (Lerp<T>::playHead > Lerp<T>::playTime)
				Lerp<T>::playHead = Lerp<T>::playTime;

			*(Lerp<T>::target) = Lerp<T>::startValue - (Lerp<T>::startValue - Lerp<T>::targetValue) * (Lerp<T>::playHead / Lerp<T>::playTime);

			return ( Lerp<T>::playHead < Lerp<T>::playTime );
		}
	};

}
