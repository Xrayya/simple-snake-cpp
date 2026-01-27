#pragma once

#include "core/input/input_event.hpp"
#include "core/fundamentals/position.hpp"

namespace event {
Input::Input(const InputType &type) : type_(type) {}

KeyInput::KeyInput(const KeyCode &keyCode, const KeyModifiers &modifiers,
                   const bool &pressed)
    : event::Input(InputType::Key), key_code_(keyCode), modifiers_(modifiers),
      pressed_(pressed) {}

MouseInput::MouseInput(const ContinousPosition &pos, bool &pressed)
    : Input(InputType::Mouse), pos_(pos), pressed_(pressed) {}
} // namespace event
