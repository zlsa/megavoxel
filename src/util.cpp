
#include "util.hpp"
#include <algorithm>

float clamp(float n, float lower, float upper) {
  return std::max(lower, std::min(n, upper));
}

int clamp(int n, int lower, int upper) {
  return std::max(lower, std::min(n, upper));
}
