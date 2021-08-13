#include "assets.h"

std::string Assets::loadText(std::string fileName) {
    std::string str;
    str = "assets/" + fileName;

    FILE* f = fopen(str.c_str(), "rb");
    if(f) {
        str = "";
        while(!feof(f)) {
            char buffer[1024] { 0 };
            fgets(buffer, 1024, f);
            
            str += std::string(buffer);
        }

        fclose(f);
    }

    return str;
}