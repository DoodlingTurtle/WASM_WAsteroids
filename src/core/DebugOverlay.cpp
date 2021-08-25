#include "./DebugOverlay.h"

DebugOverlay::DebugOverlay(olc::vf2d p) 
	: GameObject({ GameObject::DEBUG })
	, pos(p) 
{}

void DebugOverlay::onDraw(olc::PixelGameEngine* pge) {
	std::string s;

	for (auto i : items) {
		s += i.l + ": ";
		std::string fill = std::string(i.l.length() + 2, ' ') + "\n";
		int ptrAdv = fill.length() + 1;
		std::string out;
		int ptr = 0;

		switch (i.t) {
			#define REGISTER_DEBUGTYPE(x, l, st) case DebugOverlay::TYPE_##l: out = st; break;
			#include "DebugOverlay.hpp"
		}

		while (std::string::npos != (ptr = out.find("\n", ptr))) {\
			out.replace(ptr, 1, fill);
			ptr+=ptrAdv;
		}

		s += out + "\n";
	}

	pge->DrawStringDecal(pos, s, olc::WHITE);
}

void DebugOverlay::addItem(std::string label, DebugOverlay::Type type, void* data) {

	DebugOverlay::_data d;

	switch (type) {
        #define REGISTER_DEBUGTYPE(ty, l, s) case DebugOverlay::TYPE_##l: d.t##l = (ty*)data; break;
		#include "DebugOverlay.hpp"
	}

	items.push_back({ label, type, d });
}
