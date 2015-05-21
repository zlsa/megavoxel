
#include <iostream>

#include "util.hpp"
#include "log.hpp"

static std::string log_colors[] = {
  "\33[32m",
  "\33[34m",
  "\33[36m",
  "\33[35m",
  "\33[33m",
  "\33[31m",
  "\33[31m",
};

void log(int level, std::string message) {
  std::string prefix;
  
  switch(level) {
  case LOG_LEVEL_VOMIT:
    prefix = "  ";
    break;
  case LOG_LEVEL_DEBUG:
    prefix = "D ";
    break;
  case LOG_LEVEL_INFO:
    prefix = "* ";
    break;
  case LOG_LEVEL_NOTICE:
    prefix = "= ";
    break;
  case LOG_LEVEL_WARN:
    prefix = "! ";
    break;
  case LOG_LEVEL_ERROR:
    prefix = "! ";
    break;
  case LOG_LEVEL_FATAL:
    prefix = "! ";
    break;
  default:
    prefix = "? ";
    break;
  }

  #if LOG_USE_COLOR
  std::cout << log_colors[level] << prefix << message << "\33[0m" << std::endl;
  #else
  std::cout << prefix << message << std::endl;
  #endif

  if(level == LOG_LEVEL_FATAL) {
    throw exit_exception();
  }
  
}
