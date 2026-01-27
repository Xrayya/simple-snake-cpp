#include "apple.hpp"
#include "core/fundamentals/position.hpp"

Apple::Apple(int layoutWidth, int layoutHeight)
    : pos(Position::random(layoutWidth, layoutHeight)) {}

auto Apple::position() -> Position { return pos; }

void Apple::update() {}

auto Apple::additionalScore() -> int { return 1; }

auto Apple::clone() const -> std::unique_ptr<IFood> {
  return std::make_unique<Apple>(*this);
}

auto Apple::eaterSizeEffect() const -> int { return 1; }
