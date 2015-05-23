
#ifndef UTIL_H
#define UTIL_H

#include <float.h>
#include <climits>
#include <vector>
#include <exception>
#include <string>
#include <boost/filesystem.hpp>

#include "config.hpp"

#define NEWLINE "\n"

class exit_exception: public std::exception {
};

class fatal_exception: public std::exception {
};

double clamp(double n, double lower, double upper=DBL_MAX);
int clamp(int n, int lower, int upper=INT_MAX);

std::string bool_to_string(bool value);

std::string vector_to_string(std::vector<std::string> vector);
std::string vector_to_string(std::vector<boost::filesystem::path> vector);

std::string until_whitespace(std::string string, int start=0, bool semicolon=false);
int over_whitespace(std::string string, int start=0, bool semicolon=false);
int until_newline(std::string string, int start=0);
  
std::string plural(int value, std::string single = "", std::string other = "s");
std::string plural(double value, std::string single = "", std::string other = "s");

#endif
