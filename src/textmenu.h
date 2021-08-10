#ifndef __TextMenu_H__
#define __TextMenu_H__

#include "olcPixelGameEngine.h"
#include <vector>
#include <string>
#include "transform.h"

    enum TextMenuType {
        TEXTMENU_LIST,
        TEXTMENU_LINE,
        TEXTMENU_SINGLE_HORIZONTAL,
        TEXTMENU_SINGLE_VERTICAL
    };

    class TextMenu {
    public:
        TextMenu(TextMenuType textMenuType=TEXTMENU_LIST);
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
        char cursor; 
        int iSelected;

    private:
        int maxlength;
        TextMenuType type;
    };
#endif
