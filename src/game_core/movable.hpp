#pragma once

#include "game_core/actor.hpp"
#include "game_core/direction.hpp"

namespace actor {
class Movable : public Actor {
public:
  Movable() = default;

  [[nodiscard]] virtual auto getDirection() const -> const Direction & = 0;
  virtual auto setDirection(const Direction &dir) -> void = 0;

  virtual auto onMove() -> void = 0;
};
} // namespace actor
