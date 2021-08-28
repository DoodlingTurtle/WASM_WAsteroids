#include <SDL/SDL_mixer.h>

#include "./engine/olcPixelGameEngine.h"
#include "./engine/Global.h"
#include "./scenes/loadscreen.h"

#include "./gameobjects/ship/shipstats.h"

#include "./config.h"

using namespace RGNDS;

//EMSCRIPTEN_KEEPALIVE int number = 0;
// Override base class with your custom functionality
class WAsteroids 
	: public Game
{
public:

	WAsteroids() : Game(new LoadScreen()) {}

	bool OnUserCreate() override {

		// setup layers
		auto _setupLayer = [this](bool en = true, std::function<void()> fnc = []() {}) {
			int ret = CreateLayer();
			SetDrawTarget(ret);
			Clear(olc::BLANK);
			fnc();
			EnableLayer(ret, en);
			return ret;
		};

		layer_blackout = _setupLayer(false, [this]() {
			SetPixelMode(olc::Pixel::ALPHA);
			Clear(olc::Pixel{ 0, 0, 0, 128 });
			SetPixelMode(olc::Pixel::NORMAL);
			});
		layer_ship = _setupLayer();
		layer_asteroids = _setupLayer();
		layer_shots = _setupLayer();
		layer_particles = _setupLayer();
		layer_stars = _setupLayer(true, [this]() {
			for (int a = 0; a < CNT_STARS; a++) {
				uint8_t i = 96 + (rand() % 64);
				Draw(
					rand() % Global::layout->app_width,
					rand() % Global::layout->app_height,
					olc::Pixel(i, i, i, 255)
				);
			}
			});

		SetDrawTarget(layer_particles);
		Clear(olc::BLANK);
		SetDrawTarget(nullptr);

		return true;
	}

	bool OnUserUpdate(float dt) override {
		SetDrawTarget(layer_particles);
		Clear(olc::BLANK);
		SetDrawTarget(nullptr);

		return Game::OnUserUpdate(dt);
	}

};


int main()
{
	// Setup SDL_Mixer
	bool run = true;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		Debug("failed to init audio device");
		run = false;
	}

	if (run) {
		//Setup global ressources
		// layout has to be set, in very first play, otherwise everything else explodes
		// TODO: store and get layout via Browser localStorage
		int screenLayout = 1;
		Global::layout = &screenLayouts[screenLayout];

		ShipStats stats;
		Global::shipStats = &stats;

		WAsteroids* game = new WAsteroids();
		if(game->Construct(
			Global::layout->app_width,
			Global::layout->app_height,
			Global::layout->app_scale,
			Global::layout->app_scale,
			false, true
		)) game->Start();
		delete game;

		Mix_HaltChannel(-1);
		switchBGMusic(nullptr);

		// Close SDL_Mixer
		Mix_CloseAudio();
		Mix_Quit();
	}

	return 0;
}

