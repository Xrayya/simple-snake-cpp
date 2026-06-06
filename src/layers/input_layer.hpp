#pragma once

#include "app_core/input/raylib_input.hpp"
#include "core/layer.hpp"

namespace layers {

class InputLayer : public core::Layer {
public:
  InputLayer();

  void OnEvent(core::Event &event) override;
  void OnUpdate(float deltaTime) override;
  void OnRender() override;

private:
  RaylibInputHandler input_handler_;
};

} // namespace layers
