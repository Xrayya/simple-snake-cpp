#include "raylib_renderer.hpp"
#include <format>
#include <memory>
#include <raylib.h>

RaylibRenderer::RaylibRenderer(std::shared_ptr<Game> game, int cellSize)
    : IRenderer(std::move(game)), cellSize(cellSize) {

  InitWindow(game_->getWidth() * cellSize, (game_->getHeight() * cellSize) + 40,
             "Snake");
  SetTargetFPS(60);
}

RaylibRenderer::~RaylibRenderer() { CloseWindow(); }

void RaylibRenderer::render() {
  BeginDrawing();
  ClearBackground(BLACK);

  // Draw score
  DrawText(std::format("Score: {}", game_->getScore()).c_str(), 10, 10, 20,
           WHITE);

  // Draw foods
  for (const auto &food : game_->getAciveFoods()) {
    auto pos = food->position();
    DrawRectangle(pos.x * cellSize, (pos.y * cellSize) + 40, cellSize, cellSize,
                  RED);
  }

  // Draw snake
  for (const auto &node : game_->getSnake()) {
    DrawRectangle(node.pos.x * cellSize, (node.pos.y * cellSize) + 40, cellSize,
                  cellSize, GREEN);
  }

  EndDrawing();
}
