
#ifndef LOG_H
#define LOG_H

#define LOG_LEVEL_VOMIT  (0)
#define LOG_LEVEL_DEBUG  (1)
#define LOG_LEVEL_INFO   (2)
#define LOG_LEVEL_NOTICE (3)
#define LOG_LEVEL_WARN   (4)
#define LOG_LEVEL_ERROR  (5)
#define LOG_LEVEL_FATAL  (6)

#define LOG_USE_COLOR (1)

void log(int level, std::string message);

#endif
