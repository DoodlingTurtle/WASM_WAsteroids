#pragma once

#include "../engine/olcPixelGameEngine.h"
#include "../engine/world/Object.h"
#include "../engine/world/components/Drawable.h"

#include "../gamecomponents.h"

using namespace RGNDS;

namespace RGNDS::UI {

	class DebugOverlay
		: public GameObject
		, public World::Drawable
	{
	public:
		DebugOverlay(olc::vf2d pos = { 0, 0 });

		enum Type {
#define REGISTER_DEBUGTYPE(t, l, s) TYPE_##l,
#include "./DebugOverlay.hpp"
		};

		void onDraw(olc::PixelGameEngine* pge) override;
		void addItem(std::string label, Type t, void* data);

		olc::vf2d pos;

	private:
		union _data {
#define REGISTER_DEBUGTYPE(ty, l, s) ty* t##l;
#include "./DebugOverlay.hpp"
		};
		struct _displayItem {
			std::string l;
			Type t;
			_data d;
		};

	protected:
		std::vector<_displayItem> items;

	};
}
