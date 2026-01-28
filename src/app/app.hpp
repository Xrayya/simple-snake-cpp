#pragma once

#include "game_core/game.hpp"
#include "game_core/renderer/renderer.hpp"
#include <memory>

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
  std::unique_ptr<IRenderer> renderer;
};
