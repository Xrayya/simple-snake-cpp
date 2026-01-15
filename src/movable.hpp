#pragma once

#include "direction.hpp"

class IMovable {
public:
  virtual void move(Direction) = 0;
};
