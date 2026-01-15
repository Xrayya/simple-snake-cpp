#include "food.hpp"
#include "position.hpp"
#include "snake.hpp"
#include <memory>
#include <vector>

class Game {
public:
  int score;
  Snake snake;
  std::vector<std::unique_ptr<IFood>> foods;
  std::vector<std::vector<char>> field;

  Game(int width, int height)
      : snake(Position(width / 2, height / 2)),
        field(height, std::vector<char>(width, ' ')) {}

  bool isGameOver();
};
