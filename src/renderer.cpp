#include "renderer.hpp"
#include "icon.hpp"
#include <iostream>

Renderer::Renderer(const Game &game) : game(game) {}

void Renderer::render() {
  std::cout << Icon::Boundary::TopLeftCorner;
  for (int i = 0; static_cast<unsigned long>(i) < game.field[0].size();
       i++) {
    std::cout << Icon::Boundary::Horizontal;
  }
  std::cout << Icon::Boundary::TopRightCorner << std::endl;

  for (auto line : game.field) {
    std::cout << Icon::Boundary::Vertical;
    for (auto c : line) {
      std::cout << c;
    }
    std::cout << Icon::Boundary::Vertical << std::endl;
  }

  std::cout << Icon::Boundary::BonttomLeftCorner;
  for (int i = 0; static_cast<unsigned long>(i) < game.field[0].size();
       i++) {
    std::cout << Icon::Boundary::Horizontal;
  }
  std::cout << Icon::Boundary::BottomRightCorner;
}
