#pragma once

#include "core/game.hpp"
#include <memory>

class IRenderer {
public:
  IRenderer(std::shared_ptr<Game> game);

  IRenderer(const IRenderer &) = default;
  IRenderer(IRenderer &&) = delete;
  auto operator=(const IRenderer &) -> IRenderer & = default;
  auto operator=(IRenderer &&) -> IRenderer & = delete;

  virtual ~IRenderer() = default;

  std::shared_ptr<Game> game_;

  virtual void render() = 0;
};
