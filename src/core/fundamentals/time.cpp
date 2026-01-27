#include "time.hpp"

TimeContext::TimeContext()
    : deltaTime(0.0F), totalTime(0.0F),
      lastFrameTime(std::chrono::high_resolution_clock::now()) {}

auto TimeContext::getDeltaTime() const -> float { return deltaTime; }

auto TimeContext::getTotalTime() const -> float { return totalTime; }

void TimeContext::reset() {
  deltaTime = 0.0F;
  totalTime = 0.0F;
  lastFrameTime = std::chrono::high_resolution_clock::now();
}

void TimeContext::update() {
  auto currentTime = std::chrono::high_resolution_clock::now();
  deltaTime = std::chrono::duration<float>(currentTime - lastFrameTime).count();
  totalTime += deltaTime;
  lastFrameTime = currentTime;
}
