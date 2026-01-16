#include "position.hpp"
#include "core/utils/utils.hpp"

Position::Position(int x, int y) : x(x), y(y) {}

bool Position::operator==(const Position &other) const {
  return x == other.x && y == other.y;
}

Position Position::random(int layoutWidth, int layoutHeight) {
  return Position(generateRandomNum<int>(0, layoutWidth - 1),
                  generateRandomNum<int>(0, layoutHeight - 1));
}
