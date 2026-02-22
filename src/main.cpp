#include "app/basic_food_factory.hpp"
#include "app_core/input/input.hpp"
#include "app_core/input/raylib_input.hpp"
#include "game_core/food_factory.hpp"
#include "game_core/game.hpp"
#include "game_core/layout.hpp"
#include "game_core/renderer/raylib_renderer.hpp"
#include "game_core/renderer/renderer.hpp"
#include "game_core/time.hpp"
#include <cstdio>
#include <iostream>
#include <memory>

auto main() -> int {
  std::shared_ptr<TimeContext> time_context = std::make_shared<TimeContext>();

  const Layout layout{.width_ = 40, .height_ = 40};

  std::unique_ptr<InputHandler> input = std::make_unique<RaylibInputHandler>();
  std::unique_ptr<IFoodFactory> food_factory =
      std::make_unique<BasicFoodFactory>(layout);
  std::shared_ptr<Game> game =
      std::make_shared<Game>(layout, std::move(food_factory), time_context, 6);

  std::unique_ptr<Renderer> renderer =
      std::make_unique<RaylibRenderer>(game, 30);

  std::unique_ptr<event::Input> input_event;
  time_context->resetTime();
  while (game->isRunning()) {
    time_context->update();
    renderer->render();
    input_event = input->poll();
    game->submitInputEvent(std::move(input_event));
    game->update();
  }

  std::cout << '\n' << "Press Enter to exit..." << '\n';
  getchar();

  return 0;
}
