#include "core/input_dispatcher.hpp"
#include "raylib.h"

namespace core {

void InputDispatcher::Poll() {
  // Check window close
  if (WindowShouldClose()) {
    EmitEvent(std::make_unique<WindowCloseEvent>());
    return;
  }

  // Check key presses
  for (int key = 0; key < 512; key++) {
    if (IsKeyPressed(key)) {
      EmitEvent(std::make_unique<KeyPressedEvent>(key));
    }
  }

  // Can add more input types here as needed:
  // - MouseButtonPressedEvent
  // - MouseMovedEvent
  // - etc.
}

} // namespace core
