#include "layers/input_layer.hpp"
#include "app_core/input/input_event.hpp"
#include "core/event.hpp"
#include "raylib.h"
#include <memory>

namespace layers {

InputLayer::InputLayer() : core::Layer("InputLayer") {}

void InputLayer::OnEvent(core::Event & /*event*/) {}

void InputLayer::OnUpdate(float /*deltaTime*/) {
  if (WindowShouldClose()) {
    SubmitEvent(std::make_unique<core::WindowCloseEvent>());
    return;
  }

  auto input_event = input_handler_.poll();

  if (input_event->type_ != InputType::Key) {
    return;
  }

  const auto *key_input = dynamic_cast<event::KeyInput *>(input_event.get());
  if (key_input == nullptr) {
    return;
  }

  SubmitEvent(std::make_unique<core::KeyPressedEvent>(key_input->key_code_));
}

void InputLayer::OnRender() {}

} // namespace layers
