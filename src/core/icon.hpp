#pragma once

#include <string>

struct Icon {
  struct Snake {
    static const char Head = '@';
    static const char Body = 'o';
  };
  struct Boundary {
    static constexpr std::string TopLeftCorner = "╭";
    static constexpr std::string TopRightCorner = "╮";
    static constexpr std::string BonttomLeftCorner = "╰";
    static constexpr std::string BottomRightCorner = "╯";
    static constexpr std::string Horizontal = "─";
    static constexpr std::string Vertical = "│";
  };
  static const char Food = '$';
};
