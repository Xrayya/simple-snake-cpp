#include "game.hpp"

class Renderer {
public:
  Renderer(const Game &game) : game(game) {}

  const Game &game;

  void render();
};
