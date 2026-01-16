#include "game.hpp"
#include "food/food.hpp"

Game::Game(int width, int height)
    : snake(Position(width / 2, height / 2)),
      field(height, std::vector<std::string>(width, " ")) {
  for (const auto &node : snake) {
    field[node.pos.y][node.pos.x] = 'o';
  }
}

void Game::update() {
  for (auto &food : foods) {
    food->update();
  }
  snake.move();
  if (auto food = checkFoodEaten()) {
    score += food->getAdditionScore();
  }
}

bool Game::isGameRunning() {
  for (auto &node : snake) {
    if (node.pos == snake.getHeadPosition()) {
      return false;
    }
  }

  return !checkSnakeCollideWithBoundaries();
}

IFood *Game::checkFoodEaten() {
  for (auto &food : foods) {
    if (food->position() == snake.getHeadPosition()) {
      return food.get();
    }
  }

  return nullptr;
}

bool Game::checkSnakeCollideWithBoundaries() {
  const auto &snakeHeadPos = snake.getHeadPosition();

  if (snakeHeadPos.x < 0 || snakeHeadPos.y < 0 ||
      static_cast<unsigned long>(snakeHeadPos.y) >= field.size() ||
      static_cast<unsigned long>(snakeHeadPos.x) >= field[0].size()) {
    return true;
  }

  return false;
}
