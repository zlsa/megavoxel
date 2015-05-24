
#include "util.hpp"
#include <algorithm>
#include <cctype>

double clamp(double n, double lower, double upper) {
  return(std::max(lower, std::min(n, upper)));
}

int clamp(int n, int lower, int upper) {
  return(std::max(lower, std::min(n, upper)));
}

std::string bool_to_string(bool value) {
  if(value) return("true");
  return("false");
}

std::string vector_to_string(std::vector<std::string> vector) {
  std::string s;
  int i = 0;
  s += "[";
  for(auto item : vector) {
    if(i > 0) s += ", ";
    s += item;
    i += 1;
  }
  s += "]";
  return(s);
}

std::string vector_to_string(std::vector<boost::filesystem::path> vector) {
  std::string s;
  int i = 0;
  s += "[";
  for(auto item : vector) {
    if(i > 0) s += ", ";
    s += item.string();
    i += 1;
  }
  s += "]";
  return(s);
}

std::string plural(int value, std::string single, std::string other) {
  if(value == 1) return single;
  return other;
}

std::string plural(float value, std::string single, std::string other) {
  if(value == 1.0) return single;
  return other;
}

// file io

std::string readFile(std::string filename) {
  std::ifstream file(filename);
  std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  return content;
}

std::string readDataFile(std::string directory, std::string filename) {
  boost::filesystem::path dir(DATA_DIRECTORY / boost::filesystem::path(directory));
  boost::filesystem::path path(dir / boost::filesystem::path(filename));
  
  std::ifstream file(path.string());
  std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  return content;
}
