#pragma once

#include "app_core/input/input.hpp"

class RaylibInputHandler : public InputHandler {
public:
  [[nodiscard]] auto poll() const -> std::unique_ptr<event::Input> override;
};
