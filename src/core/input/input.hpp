#pragma once

#include "core/input/input_event.hpp"
#include <memory>

class InputHandler {
public:
  InputHandler() = default;

  InputHandler(const InputHandler &) = default;
  InputHandler(InputHandler &&) = delete;
  auto operator=(const InputHandler &) -> InputHandler & = default;
  auto operator=(InputHandler &&) -> InputHandler & = delete;

  virtual ~InputHandler() = default;

  [[nodiscard]] virtual auto poll() const -> std::unique_ptr<event::Input> = 0;
};
