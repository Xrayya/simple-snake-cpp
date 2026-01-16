#pragma once

#include "../core/position.hpp"

class IFood {
public:
  virtual ~IFood() = default;
  virtual const Position &position() const = 0;
  virtual int scoreAddition() = 0;
};
