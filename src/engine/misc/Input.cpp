#include "../Input.h"
#include "../Global.h"

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
        olc::O,
        olc::L,
        olc::BACK,
        olc::ENTER
    };

    Input::Input()
        :keys_held(0), keys_last_held(0),
        keys_pressed(0), keys_released(0), 
        held(0), pressed(0), released(0)
    {}
    Input::~Input() {}

    void Input::updateInputs(olc::PixelGameEngine* pge) {

        //TODO: Turn this into ALT+F4 (somehow)
        _exit = (
            pge->GetKey(olc::F4).bPressed &&
            pge->GetKey(olc::CTRL).bHeld
        );

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

    bool Input::exitCombo() { return _exit; }
}
