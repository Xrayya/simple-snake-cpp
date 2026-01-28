#include "game_core/renderer/raylib_renderer.hpp"
#include "raylib.h"
#include <format>
#include <memory>

RaylibRenderer::RaylibRenderer(std::shared_ptr<Game> game, int cellSize)
    : IRenderer(std::move(game)), cellSize(cellSize) {

  InitWindow(game_->getLayout().width_ * cellSize,
             (game_->getLayout().height_ * cellSize) + 40, "Snake");
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
    auto pos = food->getCentralPosition();
    DrawRectangle(pos.x_ * cellSize, (pos.y_ * cellSize) + 40, cellSize,
                  cellSize, RED);
  }

  // Draw snake
  for (const auto &node : game_->getSnake()) {
    DrawRectangle(node.getCentralPosition().x_ * cellSize,
                  (node.getCentralPosition().y_ * cellSize) + 40, cellSize,
                  cellSize, GREEN);
  }

  EndDrawing();
}
