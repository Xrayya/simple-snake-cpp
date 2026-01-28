#pragma once

#include "game_core/layout.hpp"
class Position {
public:
  int x_, y_;

  auto operator==(const Position &other) const -> bool;

  static auto random(const Layout &layout) -> Position;
};

class ContinousPosition {
public:
  float x_, y_;

  auto operator==(const ContinousPosition &other) const -> bool;
};
