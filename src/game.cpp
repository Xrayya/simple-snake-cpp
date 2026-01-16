#include "game.hpp"

Game::Game(int width, int height)
    : snake(Position(width / 2, height / 2)),
      field(height, std::vector<std::string>(width, " ")) {
  for (const auto &node : snake) {
    field[node.pos.y][node.pos.x] = 'o';
  }
}

bool Game::isGameOver() { return false; }
