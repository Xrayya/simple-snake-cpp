#pragma once

#include "renderer.hpp"

class RaylibRenderer : public IRenderer {
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
};
