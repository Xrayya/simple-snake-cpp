#pragma once

#include "game.hpp"
#include <string>
#include <vector>

class Renderer {
public:
  Renderer(const Game &game);

  const Game &game;

  void render();

private:
  void update();
  std::vector<std::vector<std::string>> layout;
};
