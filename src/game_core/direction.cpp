#include "game_core/direction.hpp"

auto isOppositeDirection(std::pair<Direction, Direction> directions) -> bool {
  switch (directions.first) {
  case Direction::Up:
    return directions.second == Direction::Down;
  case Direction::Down:
    return directions.second == Direction::Up;
  case Direction::Left:
    return directions.second == Direction::Right;
  case Direction::Right:
    return directions.second == Direction::Left;
  }
  return false;
}
