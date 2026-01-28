#pragma once

#include "game_core/actor.hpp"
#include "game_core/consumable.hpp"

namespace actor {
class Consumer : public Actor {
public:
  Consumer() = default;

  [[nodiscard]] virtual auto canConsume(const Consumable &consumable) const
      -> bool = 0;

  virtual auto consume(const Consumable &consumable) -> void = 0;
};
} // namespace actor
