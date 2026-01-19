#include "app/basic_food_factory.hpp"
#include "core/game.hpp"
#include "core/input/raylib_input.hpp"
#include "core/renderer/raylib_renderer.hpp"
#include "core/renderer/renderer.hpp"
#include <cstdio>
#include <iostream>
#include <memory>

int main() {
  int width = 40, height = 40;
  TimeContext timeContext;

  std::unique_ptr<IInputHandler> input = std::make_unique<RaylibInputHandler>();
  std::unique_ptr<IFoodFactory> foodFactory =
      std::make_unique<BasicFoodFactory>(width, height);
  Game game(width, height, std::move(foodFactory), std::move(input),
            timeContext, 8);

  std::unique_ptr<IRenderer> renderer =
      std::make_unique<RaylibRenderer>(game, 30);

  while (game.isRunning()) {
    timeContext.update();
    renderer->render();
    game.update();
  }

  std::cout << std::endl << "Press Enter to exit..." << std::endl;
  getchar();

  return 0;
}
