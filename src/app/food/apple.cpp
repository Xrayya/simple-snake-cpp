#include "app/food/apple.hpp"

namespace actor {
Apple::Apple(const Position &pos) : pos_(pos) {}

auto Apple::getCentralPosition() const -> const Position & { return pos_; }

auto Apple::setCentralPosition(const Position &pos) -> void { pos_ = pos; }

auto Apple::getOccupiedPositions() const -> std::vector<Position> {
  return {pos_};
}

auto Apple::onUpdate() -> void {}

auto Apple::getAdditionalScore() const -> const int & {
  static const int score = 1;
  return score;
}

auto Apple::getEaterSizeEffect() const -> const int & {
  static const int sizeEffect = 1;
  return sizeEffect;
}

auto Apple::onConsume() -> bool { return true; }
} // namespace actor
