#include "layers/debug_layer.hpp"
#include "raylib.h"
#include <format>

namespace layers {

DebugLayer::DebugLayer(const GameLayer &gameLayer)
    : core::Layer("DebugLayer"), game_layer_(gameLayer) {}

void DebugLayer::OnEvent(core::Event & /*event*/) {}

void DebugLayer::OnUpdate(float /*deltaTime*/) {}

void DebugLayer::OnRender() {
  const auto fps = GetFPS();
  const auto score = game_layer_.GetGame()->getScore();

  SetWindowTitle(std::format("Snake | Score: {} | FPS: {}", score, fps).c_str());
}

} // namespace layers
