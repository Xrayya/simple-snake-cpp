#include "apple.hpp"
#include "core/fundamentals/position.hpp"

const Position Apple::position() { return Position::random(xMax, yMax); }

int Apple::getAdditionScore() { return 1; }
