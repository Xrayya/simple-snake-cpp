#pragma once

#include "game_core/renderer/renderer.hpp"
#include "raylib.h"

class RaylibRenderer : public Renderer {
public:
  RaylibRenderer(std::shared_ptr<Game>, int cellSize);

  RaylibRenderer(const RaylibRenderer &) = default;
  RaylibRenderer(RaylibRenderer &&) = delete;
  auto operator=(const RaylibRenderer &) -> RaylibRenderer & = default;
  auto operator=(RaylibRenderer &&) -> RaylibRenderer & = delete;

  ~RaylibRenderer() override;

  void render() override;

private:
  int cellSize;
  Texture2D apple_texture;
  Texture2D snake_head_texture;
  Texture2D snake_body_texture;
};
