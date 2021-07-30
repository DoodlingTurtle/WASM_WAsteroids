#include "wraparoundrenderer.h"

WrapAroundRenderer::WrapAroundRenderer() {
    drawingInstances.push_back({0,0});
}

WrapAroundRenderer::~WrapAroundRenderer() {}

void WrapAroundRenderer::updateDrawingInstances(olc::vf2d* pos, float shipRadius) {

    float halfRadius = shipRadius / 2.0f; 

    drawingInstances.clear();
    drawingInstances.reserve(4);

    // Move ship back to screen, once its true Position has left the Screen completely
    if(pos->x+halfRadius >= right)
        pos->x -= width;

    if(pos->x+halfRadius <= left)
        pos->x += width;

    if(pos->y+halfRadius >= bottom)
        pos->y -= height;

    if(pos->y+halfRadius <= top)
        pos->y += height;

    drawingInstances.push_back({ pos->x, pos->y });

    // Left Screen border wrap arround
    if(pos->x > right-shipRadius) 
        drawingInstances.push_back({ pos->x - width, pos->y });

    // Right Screen border
    else if(pos->x < left + shipRadius) 
        drawingInstances.push_back({ pos->x + width, pos->y });

    // Bottom Screen border
    if(pos->y > bottom-shipRadius) 
        drawingInstances.push_back({ pos->x, pos->y - height });

    // Top Screen border
    else if(pos->y < top + shipRadius) 
        drawingInstances.push_back({ pos->x, pos->y + height });

    // Opposit Cornor wrap around (if there is a wrap around on both x and y axis, draw a
    // fourth ship on the opposit cornor of the screen, from where the true ship is
    if(drawingInstances.size() == 3) 
        drawingInstances.push_back({
            drawingInstances[1].x
          , drawingInstances[2].y
        });
}

void WrapAroundRenderer::defineWrappingArea(int t, int r, int b, int l) {
    top = t;
    right = r;
    left = l;
    bottom = b;
    width = r - l;
    height = b - t;
}

unsigned char WrapAroundRenderer::getInstanceCnt() {
    return drawingInstances.size(); 
}

std::vector<olc::vf2d> WrapAroundRenderer::getInstances() {
    return drawingInstances;
}
