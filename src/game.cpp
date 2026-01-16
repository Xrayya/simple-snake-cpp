#include "game.hpp"

Game::Game(int width, int height)
    : snake(Position(width / 2, height / 2)), width(width), height(height) {}

const int &Game::getWidth() const { return width; }

const int &Game::getHeight() const { return height; }

// void Game::update() {
//   for (auto &food : foods) {
//     food->update();
//   }
//   snake.move();
//   if (auto food = checkFoodEaten()) {
//     score += food->getAdditionScore();
//   }
// }
//
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
