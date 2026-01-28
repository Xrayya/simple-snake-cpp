#pragma once

#include "game_core/position.hpp"
#include <vector>

namespace actor {
class Actor {
public:
  Actor() = default;

  Actor(const Actor &) = default;
  Actor(Actor &&) = delete;
  auto operator=(const Actor &) -> Actor & = default;
  auto operator=(Actor &&) -> Actor & = delete;

  virtual ~Actor() = default;

  [[nodiscard]] virtual auto getCentralPosition() const -> const Position & = 0;
  virtual auto setCentralPosition(const Position &pos) -> void = 0;

  [[nodiscard]] virtual auto getOccupiedPositions() const
      -> std::vector<Position> = 0;

  virtual auto onUpdate() -> void = 0;
};
} // namespace actor
