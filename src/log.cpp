
#include "log.hpp"

#include <iostream>

#include "program.hpp"
#include "util.hpp"

extern Program *program;

static std::string log_colors[] = {
  "\33[32m",
  "\33[01m\33[35m",
  "\33[34m",
  "\33[36m",
  "\33[35m",
  "\33[33m",
  "\33[31m",
  "\33[31m",
  "\33[31m",
};

void log(LogLevel level, std::string message, std::string filename, int line, bool force) {
  std::string prefix;

  if(program != NULL && level < program->log_level && !force) return;

  switch(level) {
   case LOG_LEVEL_DUMP:
     prefix = "  ";
     break;
   case LOG_LEVEL_VERBOSE:
     prefix = "> ";
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
   case LOG_LEVEL_INTERNAL:
     prefix = "* ";
     break;
   default:
     prefix = "? ";
     break;
  }

  if(level >= LOG_LEVEL_INTERNAL) {
    prefix += filename + " (L" + std::to_string(line) + ") ";
  }

  if(program != NULL && program->log_use_colors) {
    std::cout << log_colors[level] << prefix << message << "\33[0m" << std::endl;
  } else {
    std::cout << prefix << message << std::endl;
  }

  if(level >= LOG_LEVEL_FATAL) {
    throw fatal_exception();
  }
  
}

void log(LogLevel level, std::string message) {
  log(level, message, "<unknown>", 0, false);
}

void log(LogLevel level, std::string message, bool force) {
  log(level, message, "<unknown>", 0, force);
}
