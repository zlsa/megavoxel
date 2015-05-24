
#ifndef LOG_H
#define LOG_H

#include <string>

#define LOG_REFCOUNT 0
#define LOG_SCENEGRAPH_CHANGES 0

enum LogLevel {
  LOG_LEVEL_DUMP = 0,
  LOG_LEVEL_DEBUG,
  LOG_LEVEL_INFO,
  LOG_LEVEL_NOTICE,
  LOG_LEVEL_WARN,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_FATAL,
  LOG_LEVEL_INTERNAL,
  LOG_LEVEL_MAX
};

#define LOG_USE_COLOR (1)

void log(LogLevel level, std::string message, bool force = false);

#endif
