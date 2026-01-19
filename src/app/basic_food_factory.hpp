#pragma once

#include "core/food/food_factory.hpp"
#include <functional>
#include <memory>
#include <vector>

class BasicFoodFactory : public IFoodFactory {
public:
  BasicFoodFactory(int layoutWidth, int layoutHeight);
  std::unique_ptr<IFood> generate() override;

private:
  using FoodCreatorFunc = std::function<std::unique_ptr<IFood>()>;
  std::vector<FoodCreatorFunc> foodCreators;
};
