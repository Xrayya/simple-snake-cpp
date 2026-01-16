#include "app/basic_food_factory.hpp"
#include "core/game.hpp"
#include "core/renderer.hpp"

int main() {
  int width = 40, height = 40;
  Game game(width, height, std::make_unique<BasicFoodFactory>(width, height));
  Renderer renderer(game);

  renderer.render();

  return 0;
}
