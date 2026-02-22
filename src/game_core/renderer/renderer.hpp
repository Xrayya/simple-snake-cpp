#pragma once

#include "game_core/game.hpp"
#include <memory>

class Renderer {
public:
  Renderer(std::shared_ptr<Game> game);

  Renderer(const Renderer &) = default;
  Renderer(Renderer &&) = delete;
  auto operator=(const Renderer &) -> Renderer & = default;
  auto operator=(Renderer &&) -> Renderer & = delete;

  virtual ~Renderer() = default;

  std::shared_ptr<Game> game_;

  virtual void render() = 0;
};
