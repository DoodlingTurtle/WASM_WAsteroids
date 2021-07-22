#include "wraparoundrenderer.h"

WrapAroundRenderer::WrapAroundRenderer() {
    drawingInstances[0] = {0, 0};
}

WrapAroundRenderer::~WrapAroundRenderer() {}

void WrapAroundRenderer::updateDrawingInstances(olc::vf2d* pos, float shipRadius) {

    float halfRadius = shipRadius / 2.0f; 

    // Move ship back to screen, once its true Position has left the Screen completely
    if(pos->x+halfRadius >= right)
        pos->x -= width;

    if(pos->x+halfRadius <= left)
        pos->x += width;

    if(pos->y+halfRadius >= bottom)
        pos->y -= height;

    if(pos->y+halfRadius <= top)
        pos->y += height;


    drawingInstances[0] = { pos->x, pos->y };
    drawingInstanceCnt = 1;

    // Left Screen border wrap arround
    if(pos->x > right-shipRadius) {
        drawingInstances[drawingInstanceCnt] = { pos->x - width, pos->y };
        drawingInstanceCnt++;
    }

    // Right Screen border
    else if(pos->x < left + shipRadius) {
        drawingInstances[drawingInstanceCnt] = { pos->x + width, pos->y };
        drawingInstanceCnt++;
    }

    // Bottom Screen border
    if(pos->y > bottom-shipRadius) {
        drawingInstances[drawingInstanceCnt] = { pos->x, pos->y - height };
        drawingInstanceCnt++;
    }

    // Top Screen border
    else if(pos->y < top + shipRadius) {
        drawingInstances[drawingInstanceCnt] = { pos->x, pos->y + height };
        drawingInstanceCnt++;
    }

    // Opposit Cornor wrap around (if there is a wrap around on both x and y axis, draw a
    // fourth ship on the opposit cornor of the screen, from where the true ship is
    if(drawingInstanceCnt == 3) {
        drawingInstances[drawingInstanceCnt] = {
            drawingInstances[1].x
          , drawingInstances[2].y
        };
        drawingInstanceCnt++;
    }
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
    return drawingInstanceCnt;
}

olc::vf2d WrapAroundRenderer::getInstance(unsigned char index) {
    if(index < 0 || index > 3)
        index = 0;



    return drawingInstances[index];
}
