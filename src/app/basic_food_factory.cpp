#include "basic_food_factory.hpp"
#include "food/apple.hpp"
#include <memory>

BasicFoodFactory::BasicFoodFactory(int layoutWidth, int layoutHeight) {
  foodCreators.push_back([layoutWidth, layoutHeight]() {
    return std::make_unique<Apple>(layoutWidth, layoutHeight);
  });
}

std::unique_ptr<IFood> BasicFoodFactory::generate() {
  return (*foodCreators.begin())();
}
