#pragma once

#include "core/event.hpp"
#include "core/fundamentals/direction.hpp"
#include <memory>

enum class InputType { Uknown, Direction, Action };

enum class ActionType { Pause, Quit };

struct InputEvent : Event {
  InputType inputType;
  static InputEvent Unknown();

protected:
  InputEvent();
};

struct InputEventDirection : InputEvent {
  InputEventDirection(Direction direction);
  Direction direction;
};

struct InputEventAction : InputEvent {
  InputEventAction(ActionType action);
  ActionType action;
};

class InputHandler {
public:
  InputHandler() = default;
  explicit InputHandler(int timeout_ms);
  std::unique_ptr<InputEvent> poll() const;

private:
  int timeout_ms = 5;
};
