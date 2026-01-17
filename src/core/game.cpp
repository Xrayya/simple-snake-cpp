#include "game.hpp"

Game::Game(int width, int height, std::unique_ptr<IFoodFactory> foodFactory)
    : snake(Position(width / 2, height / 2)),
      foodFactory(std::move(foodFactory)), width(width), height(height) {
  spawnFood();
}

const int &Game::getWidth() const { return width; }

const int &Game::getHeight() const { return height; }

void Game::update() {
  for (auto &food : activeFoods) {
    food->update();
  }
  snake.move();
}

bool Game::isRunning() {
  const auto &snakeHeadPos = snake.getHeadPosition();

  // Check collision with self
  for (const auto &node : snake) {
    if (node.pos == snakeHeadPos && node != *snake.begin()) {
      return false;
    }
  }

  // Check collision with boundaries
  if (snakeHeadPos.x < 0 || snakeHeadPos.y < 0 || snakeHeadPos.y >= height ||
      snakeHeadPos.x >= width) {
    return false;
  }

  return true;
}

void Game::spawnFood() {
  auto newFood = foodFactory->generate();

  // Ensure food does not spawn on the snake
  bool confict = true;
  while (confict) {
    confict = false;
    for (const auto &node : snake) {
      if (node.pos == newFood->position()) {
        confict = true;
        newFood = foodFactory->generate();
        break;
      }
    }
  }

  activeFoods.emplace_back(std::move(newFood));
}

// bool Game::isRunning() {
//   for (auto &node : snake) {
//     if (node.pos == snake.getHeadPosition()) {
//       return false;
//     }
//   }
//
//   return !checkSnakeCollideWithBoundaries();
// }
//
// IFood *Game::checkFoodEaten() {
//   for (auto &food : foods) {
//     if (food->position() == snake.getHeadPosition()) {
//       return food.get();
//     }
//   }
//
//   return nullptr;
// }
//
// bool Game::checkSnakeCollideWithBoundaries() {
//   const auto &snakeHeadPos = snake.getHeadPosition();
//
//   if (snakeHeadPos.x < 0 || snakeHeadPos.y < 0 ||
//       static_cast<unsigned long>(snakeHeadPos.y) >= field.size() ||
//       static_cast<unsigned long>(snakeHeadPos.x) >= field[0].size()) {
//     return true;
//   }
//
//   return false;
// }
