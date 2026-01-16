#pragma once

#include "game.hpp"

class Renderer {
public:
  Renderer(const Game &game);

  const Game &game;

  void render();
};
