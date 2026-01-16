#pragma once

#include "snake/snake.hpp"
#include <vector>

class Game {
public:
  int score;
  Snake snake;
  std::vector<std::unique_ptr<IFood>> foods;
  std::vector<std::vector<std::string>> field;

  Game(int width, int height);

  bool isGameOver();
};
