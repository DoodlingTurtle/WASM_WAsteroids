#include "../Input.h"

namespace RGNDS {

    olc::Key Input::keyMap[NUM_KEYS] = {
        olc::A,
        olc::D,
        olc::W,
        olc::S,
        olc::F,
        olc::J,
        olc::K,
        olc::P,
        olc::K,
        olc::L,
        olc::BACK,
        olc::ENTER
    };

    Input::Input(olc::PixelGameEngine* pge)
        :pge(pge), keys_held(0), keys_last_held(0),
        keys_pressed(0), keys_released(0)
    {}
    Input::~Input() {}

    void Input::updateInputs() {

        unsigned int key = 0;
        for (int a = 0; a < NUM_KEYS; a++)
            if (pge->GetKey(keyMap[a]).bPressed || pge->GetKey(keyMap[a]).bHeld)
                key = key | (1 << a);

        keys_last_held = keys_held;
        keys_held = key;

        keys_pressed = (~keys_last_held) & keys_held;
        keys_released = (~keys_held) & keys_last_held;

        pressed = keys_pressed;
        released = keys_released;
        held = keys_held;

    }

}
