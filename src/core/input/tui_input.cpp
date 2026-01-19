#include "tui_input.hpp"
#include <termios.h>

TUIInputHandler::TUIInputHandler(int timeout_ms) : timeout_ms(timeout_ms) {}

std::unique_ptr<InputEvent> TUIInputHandler::poll() const {
  struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt); // save old settings
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO); // disable canonical mode and echo
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  fd_set set;
  FD_ZERO(&set);
  FD_SET(STDIN_FILENO, &set);

  struct timeval timeout;
  timeout.tv_sec = timeout_ms / 1000;
  timeout.tv_usec = (timeout_ms % 1000) * 1000;

  int rv = select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout);

  int ch = -1;
  if (rv > 0) {
    ch = getchar();
  }

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore old settings

  if (ch == -1) {
    return std::make_unique<InputEvent>(InputEvent::Unknown());
  }

  // WASD keys
  switch (ch) {
  case 'w':
    return std::make_unique<InputEventDirection>(Direction::Up);
  case 'a':
    return std::make_unique<InputEventDirection>(Direction::Left);
  case 's':
    return std::make_unique<InputEventDirection>(Direction::Down);
  case 'd':
    return std::make_unique<InputEventDirection>(Direction::Right);
  // Arrow keys (escape sequence: 27, 91, [A/B/C/D])
  case 27: {
    if (getchar() == 91) {
      switch (getchar()) {
      case 'A':
        return std::make_unique<InputEventDirection>(Direction::Up);
      case 'B':
        return std::make_unique<InputEventDirection>(Direction::Down);
      case 'C':
        return std::make_unique<InputEventDirection>(Direction::Right);
      case 'D':
        return std::make_unique<InputEventDirection>(Direction::Left);
      }
    }
    break;
  }
  case 'p':
    return std::make_unique<InputEventAction>(ActionType::Pause);
  case 'q':
    return std::make_unique<InputEventAction>(ActionType::Quit);
  default:
    break;
  }
  return std::make_unique<InputEvent>(InputEvent::Unknown());
}
