#include "app/basic_food_factory.hpp"
#include "app/food/apple.hpp"
#include "game_core/position.hpp"
#include <memory>

BasicFoodFactory::BasicFoodFactory(const Layout &layout) {
  foodCreators.emplace_back(
      [layout]() -> std::__detail::__unique_ptr_t<actor::Apple> {
        return std::make_unique<actor::Apple>(Position::random(layout));
      });
}

auto BasicFoodFactory::generate() -> std::unique_ptr<actor::Consumable> {
  return (*foodCreators.begin())();
}
