#pragma once

#include "core/food/food.hpp"
#include <memory>

class IFoodFactory {
public:
  virtual ~IFoodFactory() = default;
  virtual std::unique_ptr<IFood> generate() = 0;
};
