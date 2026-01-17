#pragma once

class Position {
public:
  int x, y;

  Position(const int &x, const int &y);
  Position() = default;

  bool operator==(const Position &other) const;

  static Position random(const int &layoutWidth, const int &layoutHeight);
};
