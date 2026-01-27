#include "app/basic_food_factory.hpp"
#include "core/game.hpp"
#include "core/input/input_event.hpp"
#include "core/input/raylib_input.hpp"
#include "core/renderer/raylib_renderer.hpp"
#include "core/renderer/renderer.hpp"
#include <cstdio>
#include <iostream>
#include <memory>

auto main() -> int {
  int width = 40;
  int height = 40;
  TimeContext timeContext;

  std::unique_ptr<InputHandler> input = std::make_unique<RaylibInputHandler>();
  std::unique_ptr<IFoodFactory> foodFactory =
      std::make_unique<BasicFoodFactory>(width, height);
  std::shared_ptr<Game> game = std::make_shared<Game>(
      width, height, std::move(foodFactory), timeContext, 8);

  std::unique_ptr<IRenderer> renderer =
      std::make_unique<RaylibRenderer>(game, 30);

  std::unique_ptr<event::Input> inputEvent;
  timeContext.reset();
  while (game->isRunning()) {
    timeContext.update();
    renderer->render();
    inputEvent = input->poll();
    game->submitInputEvent(std::move(inputEvent));
    game->update();
  }

  std::cout << '\n' << "Press Enter to exit..." << '\n';
  getchar();

  return 0;
}
