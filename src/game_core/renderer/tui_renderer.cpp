#include "game_core/renderer/tui_renderer.hpp"
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

struct Icon {
  struct Snake {
    static const char Head = '@';
    static const char Body = 'o';
  };
  struct Boundary {
    static constexpr std::string TopLeftCorner = "╭";
    static constexpr std::string TopRightCorner = "╮";
    static constexpr std::string BonttomLeftCorner = "╰";
    static constexpr std::string BottomRightCorner = "╯";
    static constexpr std::string Horizontal = "─";
    static constexpr std::string Vertical = "│";
  };
  static const char Food = '$';
};

TUIRenderer::TUIRenderer(std::shared_ptr<Game> game)
    : IRenderer(std::move(game)),
      layout(static_cast<size_t>(game_->getLayout().height_),
             std::vector<std::string>(
                 static_cast<size_t>(game_->getLayout().width_), " ")) {}

void TUIRenderer::render() {
  update();

  // Clear terminal using ANSI escape codes
  std::cout << "\033[2J\033[H";

  std::cout << "Score: " << game_->getScore() << '\n';

  std::cout << '\n';

  std::cout << Icon::Boundary::TopLeftCorner;
  for (int i = 0; i < game_->getLayout().width_; i++) {
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
  for (int i = 0; i < game_->getLayout().width_; i++) {
    std::cout << Icon::Boundary::Horizontal;
  }
  std::cout << Icon::Boundary::BottomRightCorner << '\n';

  std::cout << std::flush;
}

void TUIRenderer::update() {
  // Clear layout
  for (int i = 0; i < game_->getLayout().height_; i++) {
    for (int j = 0; j < game_->getLayout().width_; j++) {
      layout[static_cast<size_t>(i)][static_cast<size_t>(j)] = " ";
    }
  }

  // Update food on layout
  for (const auto &food : game_->getAciveFoods()) {
    const auto &foodPos = food->getCentralPosition();
    layout[static_cast<size_t>(foodPos.y_)][static_cast<size_t>(foodPos.x_)] =
        Icon::Food;
  }

  // Update snake on layout
  for (const auto &node : game_->getSnake()) {
    if (node.getFrontNode() == nullptr) {
      layout[static_cast<size_t>(node.getCentralPosition().y_)]
            [static_cast<size_t>(node.getCentralPosition().x_)] =
                Icon::Snake::Head;
    } else {
      layout[static_cast<size_t>(node.getCentralPosition().y_)]
            [static_cast<size_t>(node.getCentralPosition().x_)] =
                Icon::Snake::Body;
    }
  }
}
