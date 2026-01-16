#pragma once

#include "direction.hpp"

class IMovable {
public:
  Direction direction = Direction::Left;
  virtual void move() = 0;
};
