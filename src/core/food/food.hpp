#pragma once

#include "core/fundamentals/position.hpp"
#include <memory>

class IFood {
public:
  IFood() = default;

  IFood(const IFood &) = default;
  IFood(IFood &&) = delete;
  auto operator=(const IFood &) -> IFood & = default;
  auto operator=(IFood &&) -> IFood & = delete;

  virtual ~IFood() = default;

  virtual auto position() -> Position = 0;
  virtual void update() = 0;
  virtual auto additionalScore() -> int = 0;
  [[nodiscard]] virtual auto clone() const -> std::unique_ptr<IFood> = 0;
  [[nodiscard]] virtual auto eaterSizeEffect() const -> int = 0;
};
