#include "../UI.h"

namespace RGNDS::UI {
	/*==============================================================================
	 *TextMenu
	 *============================================================================*/
	TextMenu::TextMenu(Type menuType) {
		cursor = "* ";
		empty = std::string(cursor.size(), ' ');
		iSelected = 0;
		eType = menuType;
		maxlength = 0;
	}
	TextMenu::~TextMenu() {
		options.clear();
	}

	void TextMenu::addOption(std::string txt) {

		if (txt.length() > maxlength)
			maxlength = txt.length();

		options.push_back(txt);
	}

	void TextMenu::clearOptions() {
		options.clear();
	}

	void TextMenu::draw(olc::PixelGameEngine* pge) {
		int i = 0;

		switch (eType) {
		case TYPE_SINGLE_HORIZONTAL: {
			std::string s = "< " + options.at(iSelected) + " >";
			//TODO: Reactivate later
/*                pge->DrawString(
						transform.pos.x, transform.pos.y,
						buffer, olc::WHITE, transform.scale
						);
 */
			break;
		}
		default: {
			for (auto txt : options) {
				std::string s = ((i == iSelected) ? cursor : empty) + txt;
				i++;

				pge->DrawStringDecal(
					transform.pos,
					s, olc::WHITE, { transform.scale, transform.scale }
				);
				transform.pos.y += 10 * transform.scale;
			}
			transform.pos.y -= 10 * options.size() * transform.scale;
		}
		}
	}

	void TextMenu::selectNext() {
		int s = iSelected;
		s++;
		if (s >= (int)options.size())
			s = 0;

		iSelected = s;
	}

	void TextMenu::selectPrev() {
		int s = iSelected;
		int si = options.size();
		if (si == 0) return;

		s--;
		if (s < 0)
			s = si - 1;

		iSelected = s;
	}

	int TextMenu::selected() { return iSelected; }

	void TextMenu::setSelection(int index) {
		if (index < 0 || index >= options.size())
			return;

		iSelected = index;
	}
	int TextMenu::getPXWidth() {
		int width = maxlength;
		switch (eType) {
		case TYPE_SINGLE_HORIZONTAL:
			width += 4;
			break;
		}

		return 0.0; //width * RGNDS::GL2D::defaultFont[0].width * transform.scale;
	}

	std::string TextMenu::selectedText() {
		return options.at(iSelected);
	}




	/*==============================================================================
	 * DebugOverlay
	 *============================================================================*/
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

			while (std::string::npos != (ptr = out.find("\n", ptr))) {
				\
					out.replace(ptr, 1, fill);
				ptr += ptrAdv;
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

}


