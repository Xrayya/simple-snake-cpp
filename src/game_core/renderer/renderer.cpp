#include "game_core/renderer/renderer.hpp"

IRenderer::IRenderer(std::shared_ptr<Game> game) : game_(std::move(game)) {}
