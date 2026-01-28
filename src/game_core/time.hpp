#pragma once

#include <chrono>

class TimeContext {
public:
  TimeContext();
  [[nodiscard]] auto getDeltaTime() const -> const float &;
  [[nodiscard]] auto getTotalTime() const -> const float &;

  auto resetTime() -> void;
  auto update() -> void;

private:
  float delta_time_;
  float total_time_;
  std::chrono::high_resolution_clock::time_point last_frame_time_;
};
