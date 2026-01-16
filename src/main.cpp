#include "core/game.hpp"
#include "core/renderer.hpp"

int main() {
  Game game(40, 40);
  Renderer renderer(game);

  renderer.render();

  return 0;
}
