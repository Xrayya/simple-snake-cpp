#pragma once

#include "food/food_factory.hpp"
#include "snake/snake.hpp"
#include <memory>

class Game {
public:
  Snake snake;
  std::unique_ptr<IFoodFactory> foodFactory;

  Game(int width, int height, std::unique_ptr<IFoodFactory> foodFactory);

  const int &getWidth() const;
  const int &getHeight() const;

  // void update();
  // bool isRunning();

private:
  int width, height;
  // int score;
  // IFood *checkFoodEaten();
  // bool checkSnakeCollideWithBoundaries();
};
