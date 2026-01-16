#pragma once

struct Position {
  int x, y;

  bool operator==(const Position &other) const;
};
