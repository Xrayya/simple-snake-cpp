#pragma once

#include "game_core/renderer/renderer.hpp"
#include <string>
#include <vector>

class TUIRenderer : public Renderer {
public:
  TUIRenderer(std::shared_ptr<Game> game);

  void render() override;

private:
  void update();
  std::vector<std::vector<std::string>> layout;
};
