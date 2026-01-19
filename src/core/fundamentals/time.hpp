#pragma once

#include <chrono>

class TimeContext {
public:
  TimeContext();
  float getDeltaTime() const;
  float getTotalTime() const;

  void reset();
  void update();
private:
  float deltaTime;
  float totalTime;
  std::chrono::high_resolution_clock::time_point lastFrameTime;
};
