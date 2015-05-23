
#include "util.hpp"
#include <algorithm>
#include <cctype>

float clamp(float n, float lower, float upper) {
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

std::string until_whitespace(std::string string, int start, bool semicolon) {
  char c;
  int i;

  std::string output;
  
  for(i=start; i<string.size(); i++) {
    c = string[i];
    if(isspace(c)) {
      break;
    }
    if(semicolon && c == ';') break;
    output += c;
  }

  return(output);
}

int over_whitespace(std::string string, int start, bool semicolon) {
  int i;
  for(i=start; i<string.size(); i++) {
    if(!isspace(string[i])) {
      break;
    }
    if(semicolon && string[i] != ';') break;
  }
  return(i - start);
}

int until_newline(std::string string, int start) {
  int i;
  for(i=start; i<string.size(); i++) {
    if(string[i] == '\n') {
      break;
    }
  }
  return(i - start);
}

std::string plural(int value, std::string single, std::string other) {
  if(value == 1) return single;
  return other;
}

std::string plural(float value, std::string single, std::string other) {
  if(value == 1.0) return single;
  return other;
}
