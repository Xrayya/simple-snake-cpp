#pragma once

#include <string>

struct Icon {
  struct Snake {
    char head = '@';
    char body = 'o';
  };
  struct Boundary {
    std::string topLeftCorner = "╭";
    std::string topRightCorner = "╮";
    std::string bonttomLeftCorner = "╰";
    std::string bottomRightCorner = "╯";
    std::string horizontal = "─";
    std::string vertical = "│";
  };
  std::string food = "$";
};
