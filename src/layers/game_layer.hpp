#pragma once

#include "core/layer.hpp"
#include "game_core/game.hpp"
#include "game_core/layout.hpp"
#include "game_core/renderer/renderer.hpp"
#include "game_core/time.hpp"
#include <memory>

namespace layers {

class GameLayer : public core::Layer {
public:
  GameLayer(const Layout &layout, std::shared_ptr<TimeContext> timeContext,
            int cellSize = 30, int tickPerSecond = 6);

  void OnEvent(core::Event &event) override;
  void OnUpdate(float deltaTime) override;
  void OnRender() override;

  [[nodiscard]] auto GetGame() const -> const std::shared_ptr<Game> &;

private:
  std::shared_ptr<Game> game_;
  std::shared_ptr<TimeContext> time_context_;
  std::unique_ptr<Renderer> renderer_;
  bool game_over_event_emitted_ = false;
};

} // namespace layers
