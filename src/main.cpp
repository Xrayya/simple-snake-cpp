#include "app/basic_food_factory.hpp"
#include "core/game.hpp"
#include "core/renderer.hpp"
#include <chrono>
#include <cstdio>
#include <iostream>
#include <thread>

int main() {
  int width = 40, height = 40;
  Game game(width, height, std::make_unique<BasicFoodFactory>(width, height));
  Renderer renderer(game);

  constexpr int TARGET_FPS = 10;
  constexpr auto FRAME_TIME = std::chrono::milliseconds(1000 / TARGET_FPS);

  while (game.isRunning()) {
    auto frameStart = std::chrono::steady_clock::now();

    renderer.render();

    // 1️⃣ Input
    // Direction dir = input.poll();

    game.update();

    // 4️⃣ Frame pacing
    auto frameEnd = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        frameEnd - frameStart);

    if (elapsed < FRAME_TIME) {
      std::this_thread::sleep_for(FRAME_TIME - elapsed);
    }
  }

  std::cout << std::endl << "Press Enter to exit..." << std::endl;
  getchar();

  return 0;
}
