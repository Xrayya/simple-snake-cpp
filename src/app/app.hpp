#pragma once

#include "core/game.hpp"
#include "core/renderer.hpp"

struct AppSpec {
  int width = 40, height = 40;
};

class App {
public:
  App(AppSpec appSpec);
  App();

  void run();

private:
  Game game;
  Renderer renderer;
};
