#pragma once

#include "core/input/input.hpp"

class TUIInputHandler : public InputHandler {
public:
  TUIInputHandler(int timeout_ms);
  [[nodiscard]] auto poll() const -> std::unique_ptr<event::Input> override;

private:
  int timeout_ms;
};
