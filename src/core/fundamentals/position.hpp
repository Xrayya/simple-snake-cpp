#pragma once

class Position {
public:
  int x, y;

  Position(int x, int y);
  Position() = default;

  bool operator==(const Position &other) const;
  static Position random(int xMax, int yMax);
};
