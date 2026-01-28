#include "time.hpp"

TimeContext::TimeContext()
    : delta_time_(0.0F), total_time_(0.0F),
      last_frame_time_(std::chrono::high_resolution_clock::now()) {}

auto TimeContext::getDeltaTime() const -> const float & { return delta_time_; }

auto TimeContext::getTotalTime() const -> const float & { return total_time_; }

void TimeContext::resetTime() {
  delta_time_ = 0.0F;
  total_time_ = 0.0F;
  last_frame_time_ = std::chrono::high_resolution_clock::now();
}

void TimeContext::update() {
  auto currentTime = std::chrono::high_resolution_clock::now();
  delta_time_ = std::chrono::duration<float>(currentTime - last_frame_time_).count();
  total_time_ += delta_time_;
  last_frame_time_ = currentTime;
}
