#include "game_core/renderer/raylib_renderer.hpp"
#include "raylib.h"
#include <format>
#include <memory>

enum class SpriteType : std::uint8_t { SnakeHead, SnakeBody, SnakeTail, Food };

RaylibRenderer::RaylibRenderer(std::shared_ptr<Game> game, int cellSize)
    : Renderer(std::move(game)), cellSize(cellSize),
      apple_texture{0, 0, 0, 0, 0}, snake_head_texture{0, 0, 0, 0, 0},
      snake_body_texture{0, 0, 0, 0, 0} {

  InitWindow(game_->getLayout().width_ * cellSize,
             (game_->getLayout().height_ * cellSize) + 40, "Snake");
  SetTargetFPS(60);

  Image apple = LoadImage("assets/snakesprites/png/apple_green_64.png");
  ImageResize(&apple, cellSize, cellSize);
  apple_texture = LoadTextureFromImage(apple);
  UnloadImage(apple);

  Image snake_head =
      LoadImage("assets/snakesprites/png/snake_green_head_64.png");
  ImageResize(&snake_head, cellSize, cellSize);
  snake_head_texture = LoadTextureFromImage(snake_head);
  UnloadImage(snake_head);

  Image snake_body =
      LoadImage("assets/snakesprites/png/snake_green_blob_64.png");
  ImageResize(&snake_body, cellSize, cellSize);
  snake_body_texture = LoadTextureFromImage(snake_body);
  UnloadImage(snake_body);
}

RaylibRenderer::~RaylibRenderer() {
  UnloadTexture(apple_texture);
  UnloadTexture(snake_head_texture);
  UnloadTexture(snake_body_texture);

  CloseWindow();
}

void RaylibRenderer::render() {
  BeginDrawing();
  ClearBackground(BLACK);

  // Draw score
  DrawText(std::format("Score: {}", game_->getScore()).c_str(), 10, 10, 20,
           WHITE);

  // Draw foods
  for (const auto &food : game_->getAciveFoods()) {
    auto pos = food->getCentralPosition();
    DrawTexture(apple_texture, pos.x_ * cellSize, (pos.y_ * cellSize) + 40,
                WHITE);
  }

  // Draw snake
  for (const auto &node : game_->getSnake()) {
    if (node == *game_->getSnake().begin()) {
      DrawTexture(snake_head_texture, node.getCentralPosition().x_ * cellSize,
                  (node.getCentralPosition().y_ * cellSize) + 40, WHITE);
      continue;
    }

    DrawTexture(snake_body_texture, node.getCentralPosition().x_ * cellSize,
                (node.getCentralPosition().y_ * cellSize) + 40, WHITE);
  }

  EndDrawing();
}
