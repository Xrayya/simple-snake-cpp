#include "tui_renderer.hpp"
#include "icon.hpp"
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

TUIRenderer::TUIRenderer(std::shared_ptr<Game> game)
    : IRenderer(std::move(game)),
      layout(static_cast<size_t>(game_->getHeight()),
             std::vector<std::string>(static_cast<size_t>(game_->getWidth()),
                                      " ")) {}

void TUIRenderer::render() {
  update();

  // Clear terminal using ANSI escape codes
  std::cout << "\033[2J\033[H";

  std::cout << "Score: " << game_->getScore() << '\n';

  std::cout << '\n';

  std::cout << Icon::Boundary::TopLeftCorner;
  for (int i = 0; i < game_->getWidth(); i++) {
    std::cout << Icon::Boundary::Horizontal;
  }
  std::cout << Icon::Boundary::TopRightCorner << '\n';

  for (const auto &line : layout) {
    std::cout << Icon::Boundary::Vertical;
    for (const auto &cell : line) {
      std::cout << cell;
    }
    std::cout << Icon::Boundary::Vertical << '\n';
  }

  std::cout << Icon::Boundary::BonttomLeftCorner;
  for (int i = 0; i < game_->getWidth(); i++) {
    std::cout << Icon::Boundary::Horizontal;
  }
  std::cout << Icon::Boundary::BottomRightCorner << '\n';

  std::cout << std::flush;
}

void TUIRenderer::update() {
  // Clear layout
  for (int i = 0; i < game_->getHeight(); i++) {
    for (int j = 0; j < game_->getWidth(); j++) {
      layout[static_cast<size_t>(i)][static_cast<size_t>(j)] = " ";
    }
  }

  // Update food on layout
  for (const auto &food : game_->getAciveFoods()) {
    const auto &foodPos = food->position();
    layout[static_cast<size_t>(foodPos.y)][static_cast<size_t>(foodPos.x)] =
        Icon::Food;
  }

  // Update snake on layout
  for (const auto &node : game_->getSnake()) {
    if (node.frontNode == nullptr) {
      layout[static_cast<size_t>(node.pos.y)][static_cast<size_t>(node.pos.x)] =
          Icon::Snake::Head;
    } else {
      layout[static_cast<size_t>(node.pos.y)][static_cast<size_t>(node.pos.x)] =
          Icon::Snake::Body;
    }
  }
}
