#pragma once

class IMovable {
public:
  virtual ~IMovable() = default;
  virtual void move() = 0;
};
