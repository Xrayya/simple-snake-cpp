#include "basic_food_factory.hpp"
#include "food/apple.hpp"
#include <memory>

BasicFoodFactory::BasicFoodFactory(int xMax, int yMax) {
  foodLists.emplace_back(std::make_unique<Apple>(xMax, yMax));
}

const IFood *BasicFoodFactory::generate() {
  return foodLists.begin()->get();
}
