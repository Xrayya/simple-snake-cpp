#pragma once

#include "renderer.hpp"
#include <string>
#include <vector>

class TUIRenderer : public IRenderer {
public:
  TUIRenderer(const Game &game);

  void render() override;

private:
  void update();
  std::vector<std::vector<std::string>> layout;
};
