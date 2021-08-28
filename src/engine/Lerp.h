#pragma once

namespace RGNDS {
	template <typename T> 
	class Lerp
	{
	public:
		Lerp(T* target = nullptr)
			: target(target)
			, playHead(0), playTime(0) {
			playTime = 0;
		}

		void changeTarget(T newValue, float seconds){
			if (seconds == 0) {
				*target = newValue;
				bFinished = true;
				this->startValue = newValue;
				this->targetValue = newValue;
			}
			else {
				this->startValue = *target;
				this->targetValue = newValue;

				playHead = 0;
				playTime = seconds;
				bFinished = false;
			}
		}
		void update(float deltaTime){
			// Advance Playhead
			if(!bFinished && playHead < playTime) {
				playHead += deltaTime;
				if (playHead > playTime) 
					playHead = playTime;

				bFinished = (playTime == playHead);

				*target = startValue - (startValue - targetValue) * (playHead/playTime);
			}
		}
		bool onTimelinePlay(float totalPlaytime, float playHead) {
			if(!bFinished && playHead < playTime) {
				if (playHead > playTime) 
					playHead = playTime;

				bFinished = (playTime == playHead);

				*target = startValue - (startValue - targetValue) * (playHead/playTime);
			}

			return !bFinished;
		}
		bool finished(){ return bFinished; }
		bool stop() { bFinished = true; }

	protected:
		T* target;

		T startValue;
		T targetValue;

	private:
		float playHead;
		float playTime;

		bool bFinished;

	};	
};
