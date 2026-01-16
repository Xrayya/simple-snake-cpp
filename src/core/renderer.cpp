#include "renderer.hpp"
#include "icon.hpp"
#include <iostream>
#include <string>
#include <vector>

Renderer::Renderer(const Game &game)
    : game(game),
      layout(game.getHeight(), std::vector<std::string>(game.getWidth(), " ")) {
}

void Renderer::render() {
  update();

  std::cout << Icon::Boundary::TopLeftCorner;
  for (int i = 0; i < game.getWidth(); i++) {
    std::cout << Icon::Boundary::Horizontal;
  }
  std::cout << Icon::Boundary::TopRightCorner << std::endl;

  for (auto line : layout) {
    std::cout << Icon::Boundary::Vertical;
    for (auto c : line) {
      std::cout << c;
    }
    std::cout << Icon::Boundary::Vertical << std::endl;
  }

  std::cout << Icon::Boundary::BonttomLeftCorner;
  for (int i = 0; i < game.getWidth(); i++) {
    std::cout << Icon::Boundary::Horizontal;
  }
  std::cout << Icon::Boundary::BottomRightCorner;
}

void Renderer::update() {
  // Clear layout
  for (int i = 0; i < game.getHeight(); i++) {
    for (int j = 0; j < game.getWidth(); j++) {
      layout[i][j] = " ";
    }
  }

  // Render snake
  for (const auto &node : const_cast<Snake &>(game.snake)) {
    if (!node.frontNode) {
      layout[node.pos.y][node.pos.x] = Icon::Snake::Head;
    } else {
      layout[node.pos.y][node.pos.x] = Icon::Snake::Body;
    }
  }

  // Render foods
  for (const auto &food : game.activeFoods) {
    const auto &foodPos = food->position();
    layout[foodPos.y][foodPos.x] = Icon::Food;
  }
}
