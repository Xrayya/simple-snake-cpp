#include "raylib_renderer.hpp"
#include <raylib.h>

RaylibRenderer::RaylibRenderer(const Game &game, int cellSize)
    : IRenderer(game), cellSize(cellSize) {

  InitWindow(game.getWidth() * cellSize, game.getHeight() * cellSize + 40,
             "Snake");
  SetTargetFPS(60);
}

RaylibRenderer::~RaylibRenderer() { CloseWindow(); }

void RaylibRenderer::render() {
  BeginDrawing();
  ClearBackground(BLACK);

  // Draw score
  DrawText(TextFormat("Score: %d", game.getScore()), 10, 10, 20, WHITE);

  // Draw foods
  for (const auto &food : game.getAciveFoods()) {
    auto p = food->position();
    DrawRectangle(p.x * cellSize, p.y * cellSize + 40, cellSize, cellSize, RED);
  }

  // Draw snake
  for (const auto &node : game.getSnake()) {
    DrawRectangle(node.pos.x * cellSize, node.pos.y * cellSize + 40, cellSize,
                  cellSize, GREEN);
  }

  EndDrawing();
}
