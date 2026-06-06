#pragma once

#include "core/layer.hpp"
#include "layers/game_layer.hpp"

namespace layers {

class DebugLayer : public core::Layer {
public:
  explicit DebugLayer(const GameLayer &gameLayer);

  void OnEvent(core::Event &event) override;
  void OnUpdate(float deltaTime) override;
  void OnRender() override;

private:
  const GameLayer &game_layer_;
};

} // namespace layers
