#pragma once

#include "renderer.hpp"

class RaylibRenderer : public IRenderer {
public:
  RaylibRenderer(const Game &game, int cellSize);
  ~RaylibRenderer();

  void render() override;

private:
  int cellSize;
};
