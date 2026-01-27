#pragma once

#include "core/food/food.hpp"

class Apple : public IFood {
public:
  Apple(int layoutWidth, int layoutHeight);

  auto position() -> Position override;
  void update() override;
  auto additionalScore() -> int override;
  [[nodiscard]] auto clone() const -> std::unique_ptr<IFood> override;
  [[nodiscard]] auto eaterSizeEffect() const -> int override;

private:
  Position pos;
};
