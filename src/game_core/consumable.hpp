#pragma once

#include "game_core/actor.hpp"

namespace actor {
class Consumable : public Actor {
public:
  Consumable() = default;

  [[nodiscard]] virtual auto getAdditionalScore() const -> const int & = 0;

  [[nodiscard]] virtual auto getEaterSizeEffect() const -> const int & = 0;

  virtual auto onConsume() -> bool = 0;
};
} // namespace actor
