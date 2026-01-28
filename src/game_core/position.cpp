
#include "game_core/position.hpp"
#include "game_core/utils.hpp"

auto Position::operator==(const Position &other) const -> bool {
  return x_ == other.x_ && y_ == other.y_;
}

auto Position::random(const Layout &layout) -> Position {
  return Position(generateRandomNum<int>(0, layout.width_ - 1),
                  generateRandomNum<int>(0, layout.height_ - 1));
}

auto ContinousPosition::operator==(const ContinousPosition &other) const
    -> bool {
  return x_ == other.x_ && y_ == other.y_;
}
