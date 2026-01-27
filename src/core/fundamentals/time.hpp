#pragma once

#include <chrono>

class TimeContext {
public:
  TimeContext();
  [[nodiscard]] auto getDeltaTime() const -> float;
  [[nodiscard]] auto getTotalTime() const -> float;

  auto reset() -> void;
  auto update() -> void;

private:
  float deltaTime;
  float totalTime;
  std::chrono::high_resolution_clock::time_point lastFrameTime;
};
