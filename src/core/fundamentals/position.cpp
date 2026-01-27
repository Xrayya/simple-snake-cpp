#include "position.hpp"
#include "core/utils/utils.hpp"

auto Position::operator==(const Position &other) const -> bool {
  return x == other.x && y == other.y;
}

auto Position::random(const int &layoutWidth, const int &layoutHeight)
    -> Position {
  return Position(generateRandomNum<int>(0, layoutWidth - 1),
                  generateRandomNum<int>(0, layoutHeight - 1));
}

auto ContinousPosition::operator==(const ContinousPosition &other) const -> bool {
  return x == other.x && y == other.y;
}
