#pragma once

#include <chrono>
#include <random>

template <typename T> inline auto generateRandomNum(T min, T max) -> T {
  unsigned long seed = static_cast<unsigned long>(
      std::chrono::system_clock::now().time_since_epoch().count());
  static std::mt19937 engine(seed);

  if constexpr (std::is_integral_v<T>) {
    std::uniform_int_distribution<T> dist(min, max);
    return dist(engine);
  } else {
    std::uniform_real_distribution<T> dist(min, max);
    return dist(engine);
  }
}
