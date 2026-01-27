#include "basic_food_factory.hpp"
#include "food/apple.hpp"
#include <memory>

BasicFoodFactory::BasicFoodFactory(int layoutWidth, int layoutHeight) {
  foodCreators.emplace_back([layoutWidth, layoutHeight]() -> std::__detail::__unique_ptr_t<Apple> {
    return std::make_unique<Apple>(layoutWidth, layoutHeight);
  });
}

auto BasicFoodFactory::generate() -> std::unique_ptr<IFood> {
  return (*foodCreators.begin())();
}
