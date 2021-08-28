#pragma once

#include <vector>
#include <string>

#include "../olcPixelGameEngine.h"
#include "../Transform.h"

namespace RGNDS::UI {

	class TextMenu {
	public:
		enum Type {
			TYPE_LIST,
			TYPE_LINE,
			TYPE_SINGLE_HORIZONTAL,
			TYPE_SINGLE_VERTICAL
		};

		TextMenu(Type textMenuType = TYPE_LIST);
		virtual~TextMenu();

		void addOption(const std::string txt);
		void clearOptions();

		void selectNext();
		void selectPrev();
		int selected();

		void setSelection(int index);

		int getPXWidth();

		void draw(olc::PixelGameEngine* pge);
		RGNDS::Transform transform;

		std::string selectedText();

	protected:
		std::vector<std::string> options;
		std::string cursor;
		std::string empty;
		int iSelected;

	private:
		int maxlength;
		Type eType;
	};
}
