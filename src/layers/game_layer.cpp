#include "layers/game_layer.hpp"
#include "app/basic_food_factory.hpp"
#include "app_core/input/input_event.hpp"
#include "core/event.hpp"
#include "game_core/renderer/raylib_renderer.hpp"
#include <memory>

namespace layers {

GameLayer::GameLayer(const Layout &layout, std::shared_ptr<TimeContext> timeContext,
                     int cellSize, int tickPerSecond)
    : core::Layer("GameLayer"),
      game_(std::make_shared<Game>(
          layout, std::make_unique<BasicFoodFactory>(layout), timeContext,
          tickPerSecond)),
      time_context_(std::move(timeContext)),
      renderer_(std::make_unique<RaylibRenderer>(game_, cellSize)) {}

void GameLayer::OnEvent(core::Event &event) {
  core::EventDispatcher dispatcher(event);
  dispatcher.Dispatch<core::KeyPressedEvent>([this](core::KeyPressedEvent &keyEvent) {
    game_->submitInputEvent(std::make_unique<event::KeyInput>(
        keyEvent.key_code_, KeyModifiers{}, true));
    return true;
  });
}

void GameLayer::OnUpdate(float /*deltaTime*/) {
  game_->update();

  if (!game_->isRunning() && !game_over_event_emitted_) {
    game_over_event_emitted_ = true;
    SubmitEvent(std::make_unique<core::GameOverEvent>());
  }
}

void GameLayer::OnRender() { renderer_->render(); }

auto GameLayer::GetGame() const -> const std::shared_ptr<Game> & { return game_; }

} // namespace layers
