
#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <exception>
#include <string>

#define NEWLINE "\n"

class exit_exception: public std::exception {
};

class fatal_exception: public std::exception {
};

float clamp(float n, float lower, float upper);
int clamp(int n, int lower, int upper);

std::string vector_to_string(std::vector<std::string> vector);

#endif
