#include "time.hpp"

TimeContext::TimeContext()
    : deltaTime(0.0f), totalTime(0.0f),
      lastFrameTime(std::chrono::high_resolution_clock::now()) {}

float TimeContext::getDeltaTime() const { return deltaTime; }

float TimeContext::getTotalTime() const { return totalTime; }

void TimeContext::reset() {
  deltaTime = 0.0f;
  totalTime = 0.0f;
  lastFrameTime = std::chrono::high_resolution_clock::now();
}

void TimeContext::update() {
  auto currentTime = std::chrono::high_resolution_clock::now();
  deltaTime = std::chrono::duration<float>(
                  currentTime - lastFrameTime)
                  .count();
  totalTime += deltaTime;
  lastFrameTime = currentTime;
}
