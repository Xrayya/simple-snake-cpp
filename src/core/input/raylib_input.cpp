#include "raylib_input.hpp"
#include "raylib.h"

std::unique_ptr<InputEvent> RaylibInputHandler::poll() const {
  // Direction input (WASD)
  if (IsKeyPressed(KEY_W))
    return std::make_unique<InputEventDirection>(Direction::Up);
  if (IsKeyPressed(KEY_A))
    return std::make_unique<InputEventDirection>(Direction::Left);
  if (IsKeyPressed(KEY_S))
    return std::make_unique<InputEventDirection>(Direction::Down);
  if (IsKeyPressed(KEY_D))
    return std::make_unique<InputEventDirection>(Direction::Right);

  // Direction input (Arrow keys)
  if (IsKeyPressed(KEY_UP))
    return std::make_unique<InputEventDirection>(Direction::Up);
  if (IsKeyPressed(KEY_LEFT))
    return std::make_unique<InputEventDirection>(Direction::Left);
  if (IsKeyPressed(KEY_DOWN))
    return std::make_unique<InputEventDirection>(Direction::Down);
  if (IsKeyPressed(KEY_RIGHT))
    return std::make_unique<InputEventDirection>(Direction::Right);

  // Action input
  if (IsKeyPressed(KEY_P))
    return std::make_unique<InputEventAction>(ActionType::Pause);
  if (IsKeyPressed(KEY_Q))
    return std::make_unique<InputEventAction>(ActionType::Quit);

  return std::make_unique<InputEvent>(InputEvent::Unknown());
}
