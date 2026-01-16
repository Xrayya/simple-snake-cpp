#pragma once

#include "food/food.hpp"
#include "snake/snake.hpp"
#include <vector>

class Game {
public:
  Snake snake;
  std::vector<std::unique_ptr<IFood>> foods;

  Game(int width, int height);

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
