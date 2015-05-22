
#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <vector>

enum ArgumentParseMode {
  ARGUMENT_PARSE_MODE_ARGS,             // default mode
  ARGUMENT_PARSE_MODE_VALUE,            // --abcdef THIS, -a THIS
};

enum ArgumentPrefix {
  ARGUMENT_PREFIX_NONE     = 0,     //
  ARGUMENT_PREFIX_SHORT    = 1,     // -a
  ARGUMENT_PREFIX_LONG     = 2,     // --abcdef
};

enum ArgumentFlag {
  ARGUMENT_FLAG_HELP,
  ARGUMENT_FLAG_VERSION,

  ARGUMENT_FLAG_LOG_LEVEL,
  ARGUMENT_FLAG_LOG_COLOR,
};

class Program {
 private:

 protected:
  std::vector<std::string> args;

  bool help;
  bool version;

 public:
  int log_level;
  bool log_use_colors;
  
  Program(int argc, char *argv[]);
  void parseArgs();
  ArgumentParseMode parseArg(std::string arg);
  ArgumentParseMode parseShortArg(char arg);
  ArgumentParseMode parseLongArg(std::string arg);

  void hasFlag(ArgumentFlag flag, bool value);
  void hasFlag(ArgumentFlag flag, int value);
  void hasFlag(ArgumentFlag flag);
  
  void displayHelp(bool force = false);
  void displayVersion(bool force = false);
};

class invalid_argument_exception: public std::exception {

 public:
  std::string argument;
  ArgumentPrefix prefix;
  invalid_argument_exception(ArgumentPrefix p, std::string arg) : prefix(p), argument(arg) {};
  const char *what() const throw() { return argument.c_str(); };
};

#endif
