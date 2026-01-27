#pragma once

class IMovable {
public:
  IMovable() = default;

  IMovable(const IMovable &) = default;
  IMovable(IMovable &&) = delete;
  auto operator=(const IMovable &) -> IMovable & = default;
  auto operator=(IMovable &&) -> IMovable & = delete;

  virtual ~IMovable() = default;
  virtual void move() = 0;
};
