
#include "random_helper.h"

#include <random>

namespace {
  std::random_device random_device;
  thread_local std::mt19937 random_engine(random_device());
}

NumType get_uniform_random(NumType min, NumType max) {
  std::uniform_real_distribution<NumType> rand_dist(min, max);
  return rand_dist(random_engine);
}
