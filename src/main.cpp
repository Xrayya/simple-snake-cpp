#include "core/application.hpp"
#include "game_core/layout.hpp"
#include "layers/debug_layer.hpp"
#include "layers/game_layer.hpp"
#include "layers/input_layer.hpp"
#include <memory>

auto main() -> int {
  const Layout layout{.width_ = 40, .height_ = 40};

  core::Application app;

  app.PushLayer(std::make_unique<layers::InputLayer>());

  auto game_layer = std::make_unique<layers::GameLayer>(layout, app.GetTimeContext(),
                                                         30, 6);
  const auto *game_layer_ptr = game_layer.get();

  app.PushLayer(std::move(game_layer));
  app.PushOverlay(std::make_unique<layers::DebugLayer>(*game_layer_ptr));

  app.Run();

  return 0;
}

// Previous direct wiring (kept for migration comparison):
// auto main() -> int {
//   std::shared_ptr<TimeContext> time_context = std::make_shared<TimeContext>();
//   const Layout layout{.width_ = 40, .height_ = 40};
//
//   std::unique_ptr<InputHandler> input = std::make_unique<RaylibInputHandler>();
//   std::unique_ptr<IFoodFactory> food_factory =
//       std::make_unique<BasicFoodFactory>(layout);
//   std::shared_ptr<Game> game =
//       std::make_shared<Game>(layout, std::move(food_factory), time_context, 6);
//
//   std::unique_ptr<Renderer> renderer =
//       std::make_unique<RaylibRenderer>(game, 30);
//
//   std::unique_ptr<event::Input> input_event;
//   time_context->resetTime();
//   while (game->isRunning()) {
//     time_context->update();
//     renderer->render();
//     input_event = input->poll();
//     game->submitInputEvent(std::move(input_event));
//     game->update();
//   }
//
//   std::cout << '\n' << "Press Enter to exit..." << '\n';
//   getchar();
//
//   return 0;
// }
