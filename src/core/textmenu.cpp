#include "textmenu.h"

#include <cstdio>
#include <math.h>



    TextMenu::TextMenu(TextMenuType menuType) {
        cursor = '*';
        iSelected = 0;
        type = menuType;
        maxlength = 0;
    }
    TextMenu::~TextMenu() {
        options.clear();
    }

    void TextMenu::addOption(std::string txt) {

        if(txt.length() > maxlength)
            maxlength = txt.length();

        options.push_back(txt);
    }

    void TextMenu::clearOptions() {
        options.clear();
    }

    void TextMenu::draw(olc::PixelGameEngine* pge) {
        char buffer[maxlength+6];

        char c;
        int i = 0;

        switch(type) {
            case TEXTMENU_SINGLE_HORIZONTAL: {
                sprintf(buffer, "< %s >", options.at(iSelected).c_str()); 
                std::string s(buffer);
                //TODO: Reactivate later
/*                pge->DrawString(
                        transform.pos.x, transform.pos.y,
                        buffer, olc::WHITE, transform.scale
                        );
 */                       
                break;
            }
            default: {
                for(auto txt : options) {
                    c = (i==iSelected) ? cursor : ' ';
                    i++;
                    
                    sprintf(buffer, "%c %s", c, txt.c_str()); 
                    std::string s(buffer);
                    
                    pge->DrawString(
                            transform.pos.x, transform.pos.y,
                            s, olc::WHITE, transform.scale
                            );
                    transform.pos.y += 10*transform.scale;
                }
                transform.pos.y -= 10 * options.size() * transform.scale;
            }
        }
    }

    void TextMenu::selectNext() {
        int s = iSelected;
        s++;
        if(s >= (int)options.size())
            s = 0;

        iSelected = s;
    }

    void TextMenu::selectPrev() {
        int s = iSelected;
        int si = options.size();
        if(si == 0) return ;

        s--;
        if(s < 0)
            s = si-1;

        iSelected = s;
    }

    int TextMenu::selected() { return iSelected; }

    void TextMenu::setSelection(int index) {
        if(index < 0 || index >= options.size())
            return;
        
        iSelected = index;
    }
    int TextMenu::getPXWidth() {
        int width = maxlength;
        switch(type) {
            case TEXTMENU_SINGLE_HORIZONTAL:
                width += 4;
                break;
        }

        return 0.0; //width * RGNDS::GL2D::defaultFont[0].width * transform.scale;
    }

    std::string TextMenu::selectedText() {
        return options.at(iSelected);
    }