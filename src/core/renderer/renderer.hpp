#pragma once

#include "core/game.hpp"

class IRenderer {
public:
  IRenderer(const Game &game);
  virtual ~IRenderer() = default;

  const Game &game;

  virtual void render() = 0;
};
