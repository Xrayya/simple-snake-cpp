#include "core/utils/utils.hpp"
#include <chrono>
#include <random>

template <typename T> int generateRandomInteger(T min, T max) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

  static std::mt19937 engine(seed);

  std::uniform_real_distribution<T> dist(min, max);

  return dist(engine);
}
