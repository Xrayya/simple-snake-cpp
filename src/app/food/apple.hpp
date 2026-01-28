#pragma once

#include "game_core/consumable.hpp"

namespace actor {
class Apple : public Consumable {
public:
  Apple(const Position &pos);

  [[nodiscard]] auto getCentralPosition() const -> const Position & override;
  auto setCentralPosition(const Position &pos) -> void override;

  [[nodiscard]] auto getOccupiedPositions() const
      -> std::vector<Position> override;

  auto onUpdate() -> void override;

  [[nodiscard]] auto getAdditionalScore() const -> const int & override;

  [[nodiscard]] auto getEaterSizeEffect() const -> const int & override;

  auto onConsume() -> bool override;

private:
  Position pos_;
};
} // namespace actor
