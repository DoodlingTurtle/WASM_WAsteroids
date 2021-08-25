#pragma once
namespace RGNDS {
	template <typename T> 
	class Lerp
	{
	public:
		Lerp(T* target = nullptr)
			: target(target)
			, playHead(0), playTime(0) {}

		void changeTarget(T newValue, float seconds){
			this->startValue = *target;
			this->targetValue = newValue;

			playHead = 0;
			playTime = seconds;
			bFinished = false;
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

		bool finished(){ return bFinished; }

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
