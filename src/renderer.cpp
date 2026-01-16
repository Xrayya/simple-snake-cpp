#include "renderer.hpp"
#include <iostream>

Renderer::Renderer(const Game &game) : game(game) {}

void Renderer::render() {
  for (auto line : game.field) {
    for (auto c : line) {
      std::cout << c;
    }
  }
}
