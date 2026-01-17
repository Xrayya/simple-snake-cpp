#include "apple.hpp"
#include "core/fundamentals/position.hpp"

Apple::Apple(int layoutWidth, int layoutHeight)
    : pos(Position::random(layoutWidth, layoutHeight)) {}

const Position Apple::position() { return pos; }

void Apple::update() {}

int Apple::additionalScore() { return 1; }

std::unique_ptr<IFood> Apple::clone() const {
  return std::make_unique<Apple>(*this);
}

int Apple::eaterSizeEffect() const { return 1; }
