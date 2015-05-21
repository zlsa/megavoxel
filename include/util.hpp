
#ifndef UTIL_H
#define UTIL_H

#include <exception>

#define NEWLINE "\n"

class exit_exception: public std::exception {
  virtual const char* what() const throw() {
    return "Exiting normally.";
  }
};

class fatal_exception: public std::exception {
  virtual const char* what() const throw() {
    return "Exiting very non-normally.";
  }
};

#endif
