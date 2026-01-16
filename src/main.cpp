#include "app/basic_food_factory.hpp"
#include "core/game.hpp"
#include "core/renderer.hpp"
#include <cstdio>
#include <iostream>

int main() {
  int width = 40, height = 40;
  Game game(width, height, std::make_unique<BasicFoodFactory>(width, height));
  Renderer renderer(game);

  renderer.render();

  std::cout << std::endl << "Press Enter to exit..." << std::endl;
  getchar();

  return 0;
}
