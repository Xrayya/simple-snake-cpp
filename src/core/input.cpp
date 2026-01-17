#include "input.hpp"
#include <cstdio>
#include <termios.h>
#include <unistd.h>

Direction InputHandler::poll() {
  struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt); // save old settings
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO); // disable canonical mode and echo
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  int ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore old settings

  // WASD keys
  switch (ch) {
  case 'w':
    return Direction::Up;
  case 'a':
    return Direction::Left;
  case 's':
    return Direction::Down;
  case 'd':
    return Direction::Right;
  // Arrow keys (escape sequence: 27, 91, [A/B/C/D])
  case 27: {
    if (getchar() == 91) {
      switch (getchar()) {
      case 'A':
        return Direction::Up;
      case 'B':
        return Direction::Down;
      case 'C':
        return Direction::Right;
      case 'D':
        return Direction::Left;
      }
    }
    break;
  }
  default:
    break;
  }
  return Direction::None; // fallback
}
