#pragma once

#include "core/fundamentals/movable.hpp"
#include "core/fundamentals/position.hpp"
#include <memory>

class IFood {
public:
  virtual ~IFood() = default;
  virtual const Position position() = 0;
  virtual void update() = 0;
  virtual int additionalScore() = 0;
  virtual std::unique_ptr<IFood> clone() const = 0;
  virtual int eaterSizeEffect() const = 0;
};

class IMovableFood : public IFood, IMovable {};
