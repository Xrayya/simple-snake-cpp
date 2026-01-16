#pragma once

#include <chrono>
#include <random>

template <typename T> T generateRandomNum(T min, T max) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::mt19937 engine(seed);

  if constexpr (std::is_integral<T>::value) {
    std::uniform_int_distribution<T> dist(min, max);
    return dist(engine);
  } else {
    std::uniform_real_distribution<T> dist(min, max);
    return dist(engine);
  }
}
