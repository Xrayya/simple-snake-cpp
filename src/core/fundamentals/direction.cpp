#include "direction.hpp"

bool isOppositeDirection(const Direction &a, const Direction &b) {
  switch (a) {
  case Direction::Up:    return b == Direction::Down;
  case Direction::Down:  return b == Direction::Up;
  case Direction::Left:  return b == Direction::Right;
  case Direction::Right: return b == Direction::Left;
  }
  return false;
}
