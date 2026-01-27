#pragma once

class Position {
public:
  int x, y;

  auto operator==(const Position &other) const -> bool;

  static auto random(const int &layoutWidth, const int &layoutHeight)
      -> Position;
};

class ContinousPosition {
public:
  float x, y;

  auto operator==(const ContinousPosition &other) const -> bool;
};
