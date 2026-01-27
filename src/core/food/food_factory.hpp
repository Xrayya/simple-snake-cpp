#pragma once

#include "core/food/food.hpp"
#include <memory>

class IFoodFactory {
public:
  IFoodFactory() = default;

  IFoodFactory(const IFoodFactory &) = default;
  IFoodFactory(IFoodFactory &&) = delete;
  auto operator=(const IFoodFactory &) -> IFoodFactory & = default;
  auto operator=(IFoodFactory &&) -> IFoodFactory & = delete;

  virtual ~IFoodFactory() = default;

  virtual auto generate() -> std::unique_ptr<IFood> = 0;
};
