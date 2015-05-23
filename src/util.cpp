
#include "util.hpp"
#include <algorithm>

float clamp(float n, float lower, float upper) {
  return(std::max(lower, std::min(n, upper)));
}

int clamp(int n, int lower, int upper) {
  return(std::max(lower, std::min(n, upper)));
}

std::string vector_to_string(std::vector<std::string> vector) {
  std::string s;
  int i = 0;
  for(auto item : vector) {
    if(i > 0) s += ", ";
    s += item;
    i += 1;
  }
  return(s);
}
