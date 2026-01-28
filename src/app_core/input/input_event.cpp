#include "app_core/input/input_event.hpp"

namespace event {
Input::Input(const InputType &type) : type_(type) {}

KeyInput::KeyInput(const KeyCode &keyCode, const KeyModifiers &modifiers,
                   const bool &pressed)
    : event::Input(InputType::Key), key_code_(keyCode), modifiers_(modifiers),
      pressed_(pressed) {}
} // namespace event
