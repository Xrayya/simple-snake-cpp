#pragma once

class Position {
public:
  Position(int x, int y);
  int x, y;

  bool operator==(const Position &other) const;
  static Position random(int xMax, int yMax);
};
