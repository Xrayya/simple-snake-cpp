#pragma once

#include "input.hpp"

class TUIInputHandler : public IInputHandler {
public:
  TUIInputHandler(int timeout_ms);
  std::unique_ptr<InputEvent> poll() const override;

private:
  int timeout_ms;
};
