#include "../Global.h"

namespace RGNDS {

	void Global::switchBGMusic(Mix_Music* asset) {
		Mix_HaltMusic();
		if (asset) Mix_PlayMusic(asset, -1);
	}
}
