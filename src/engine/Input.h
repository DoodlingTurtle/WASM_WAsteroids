#pragma once

#include "./olcPixelGameEngine.h"

#define NUM_KEYS 12

namespace RGNDS {

    enum KeyPadInput {
        KEYPAD_LEFT = 1,
        KEYPAD_RIGHT = 2,
        KEYPAD_UP = 4,
        KEYPAD_DOWN = 8,
        KEYPAD_L = 16,
        KEYPAD_R = 32,
        KEYPAD_Y = 64,
        KEYPAD_A = 128,
        KEYPAD_X = 256,
        KEYPAD_B = 512,
        KEYPAD_SELECT = 1024,
        KEYPAD_START = 2048
    };

    class Input {
    public:
        Input(olc::PixelGameEngine*);
        virtual ~Input();

        void updateInputs();

        unsigned int pressed;
        unsigned int released;
        unsigned int held;

    protected:
        olc::PixelGameEngine* pge;

    private:
        static olc::Key keyMap[NUM_KEYS];

        // These are the true inputs (cant be manipulated)
        unsigned int keys_last_held;
        unsigned int keys_held;
        unsigned int keys_pressed;
        unsigned int keys_released;
    };

}
