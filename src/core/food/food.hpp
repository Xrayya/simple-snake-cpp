#pragma once

#include "core/fundamentals/movable.hpp"
#include "core/fundamentals/position.hpp"

class IFood {
public:
  virtual ~IFood() = default;
  virtual const Position &position() const = 0;
  virtual void update() = 0;
  virtual int getAdditionScore();

private:
  int additionScore = 0;
};

class IMovableFood : public IFood, IMovable {};
