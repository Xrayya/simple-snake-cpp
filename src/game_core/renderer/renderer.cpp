#include "game_core/renderer/renderer.hpp"

Renderer::Renderer(std::shared_ptr<Game> game) : game_(std::move(game)) {}
