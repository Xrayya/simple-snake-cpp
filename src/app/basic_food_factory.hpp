#pragma once

#include "game_core/consumable.hpp"
#include "game_core/food_factory.hpp"
#include "game_core/layout.hpp"
#include <functional>
#include <memory>
#include <vector>

class BasicFoodFactory : public IFoodFactory {
public:
  BasicFoodFactory(const Layout &layout);
  auto generate() -> std::unique_ptr<actor::Consumable> override;

private:
  using FoodCreatorFunc = std::function<std::unique_ptr<actor::Consumable>()>;
  std::vector<FoodCreatorFunc> foodCreators;
};
