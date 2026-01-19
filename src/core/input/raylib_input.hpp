#pragma once

#include "input.hpp"

class RaylibInputHandler : public IInputHandler {
public:
  std::unique_ptr<InputEvent> poll() const override;
};
