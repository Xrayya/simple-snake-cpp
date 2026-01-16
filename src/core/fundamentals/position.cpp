#include "position.hpp"
#include "core/utils/utils.hpp"

Position::Position(int x, int y) : x(x), y(y) {}

bool Position::operator==(const Position &other) const {
  return x == other.x && y == other.y;
}

Position Position::random(int xMax, int yMax) {
  return Position(generateRandomNum(0, xMax), generateRandomNum(0, yMax));
}
