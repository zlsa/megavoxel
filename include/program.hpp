
#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <vector>

#include "path.hpp"

enum ArgumentParseMode {
  ARGUMENT_PARSE_MODE_ARGS,             // default mode (--help file.xml)
  ARGUMENT_PARSE_MODE_STRING,           // parsing a value (--abcdef THIS, -a THIS)
  ARGUMENT_PARSE_MODE_PATH,             // parsing a value (--abcdef THIS, -a THIS)
  ARGUMENT_PARSE_MODE_DOUBLE,           // parsing a value (--abcdef THIS, -a THIS)
  ARGUMENT_PARSE_MODE_INT,              // parsing a value (--abcdef THIS, -a THIS)
};

enum ArgumentPrefix {
  ARGUMENT_PREFIX_NONE     = 0,     //
  ARGUMENT_PREFIX_SHORT    = 1,     // -a
  ARGUMENT_PREFIX_LONG     = 2,     // --abcdef
  ARGUMENT_PREFIX_VALUE    = 3,     // --abcdef THIS
};

enum ArgumentFlag {
  ARGUMENT_FLAG_NONE = 0,
  
  ARGUMENT_FLAG_HELP,
  ARGUMENT_FLAG_VERSION,

  ARGUMENT_FLAG_CONFIG_USE_SYSTEM,
  ARGUMENT_FLAG_CONFIG_USE_USER,
  ARGUMENT_FLAG_CONFIG_EXTRA,

  ARGUMENT_FLAG_LOG_LEVEL,
  ARGUMENT_FLAG_LOG_COLOR,
};

class Program {
 private:

 protected:
  std::vector<std::string> args;

  bool help;
  bool version;

  bool config_use_system;
  bool config_use_user;
  std::vector<std::string> config_extra;

  ArgumentFlag value_flag;

 public:
  int log_level;
  bool log_use_colors;

  Program(int argc, char *argv[]);
  void parseArgs();
  void parseArg(std::string arg);
  void parseShortArg(char arg);
  void parseLongArg(std::string arg);
  
  void parseArgValue(ArgumentFlag flag, std::string value);

  void setFlag(ArgumentFlag flag, bool value);
  void setFlag(ArgumentFlag flag, int value);
  void setFlag(ArgumentFlag flag, std::string value);
  void setFlag(ArgumentFlag flag);
  
  void displayHelp(bool force = false);
  void displayVersion(bool force = false);
  
  void dump();
};

class invalid_argument_exception: public std::exception {

 public:
  std::string argument;
  ArgumentPrefix prefix;
  invalid_argument_exception(ArgumentPrefix p, std::string arg) : prefix(p), argument(arg) {};
  const char *what() const throw() { return argument.c_str(); };
};

#endif
