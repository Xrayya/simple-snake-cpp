#include "tui_renderer.hpp"
#include "icon.hpp"
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

TUIRenderer::TUIRenderer(const Game &game)
    : IRenderer(game),
      layout(game.getHeight(), std::vector<std::string>(game.getWidth(), " ")) {
}

void TUIRenderer::render() {
  update();

  // Clear terminal using ANSI escape codes
  std::cout << "\033[2J\033[H";

  std::cout << "Score: " << game.getScore() << std::endl;

  std::cout << std::endl;

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
  std::cout << Icon::Boundary::BottomRightCorner << std::endl;

  std::cout << std::flush;
}

void TUIRenderer::update() {
  // Clear layout
  for (int i = 0; i < game.getHeight(); i++) {
    for (int j = 0; j < game.getWidth(); j++) {
      layout[i][j] = " ";
    }
  }

  // Update food on layout
  for (const auto &food : game.getAciveFoods()) {
    const auto &foodPos = food->position();
    layout[foodPos.y][foodPos.x] = Icon::Food;
  }

  // Update snake on layout
  for (const auto &node : game.getSnake()) {
    if (!node.frontNode) {
      layout[node.pos.y][node.pos.x] = Icon::Snake::Head;
    } else {
      layout[node.pos.y][node.pos.x] = Icon::Snake::Body;
    }
  }
}
