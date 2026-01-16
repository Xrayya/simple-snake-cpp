#pragma once

#include "food/food.hpp"
#include "snake/snake.hpp"
#include <vector>

class Game {
public:
  Snake snake;
  std::vector<std::unique_ptr<IFood>> foods;
  std::vector<std::vector<std::string>> field;

  Game(int width, int height);

  void update();
  bool isGameRunning();

private:
  int score;
  IFood *checkFoodEaten();
  bool checkSnakeCollideWithBoundaries();
};
