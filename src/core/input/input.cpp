#include "input.hpp"

InputEvent::InputEvent() { this->eventType = EventType::Input; }

InputEvent InputEvent::Unknown() {
  InputEvent event;
  event.inputType = InputType::Uknown;
  return event;
}

InputEventDirection::InputEventDirection(Direction direction) {
  inputType = InputType::Direction;
  this->direction = direction;
}

InputEventAction::InputEventAction(ActionType action) {
  inputType = InputType::Action;
  this->action = action;
}
