
#include <iostream>

#include "pflight_config.hpp"

#include "program.hpp"
#include "util.hpp"
#include "log.hpp"

Program::Program(int argc, char *argv[]) {
  this->args.assign(argv, argv + argc);

  this->log_level      = LOG_LEVEL_VOMIT;
  this->log_use_colors = true;
}

void Program::parseArgs() {

  ArgumentParseMode mode = ARGUMENT_PARSE_MODE_ARGS;

  bool invalid = false;
  std::string invalid_argument;
  ArgumentPrefix invalid_prefix = ARGUMENT_PREFIX_NONE;

  for(int i=1; i<this->args.size(); i++) {
    try {
      mode = this->parseArg(this->args[i]);
    } catch(invalid_argument_exception e) {
      if(!invalid) {
        invalid = true;
        invalid_argument = e.argument;
        invalid_prefix = e.prefix;
      }
    }
  }

  if(this->help) {
    this->displayHelp(true);
    throw exit_exception();
    
  } else if(this->version) {
    this->displayVersion(true);
    throw exit_exception();
    
  } else if(invalid) {
    if(invalid_prefix == ARGUMENT_PREFIX_SHORT) {
      log(LOG_LEVEL_ERROR, "invalid short argument '" + invalid_argument + "'");
    } else if(invalid_prefix == ARGUMENT_PREFIX_LONG) {
      log(LOG_LEVEL_ERROR, "invalid long argument '" + invalid_argument + "'");
    }

    throw fatal_exception();
  }

  log(LOG_LEVEL_VOMIT, "log level: " + std::to_string(this->log_level));
  
}

ArgumentParseMode Program::parseArg(std::string arg) {
  ArgumentPrefix prefix = ARGUMENT_PREFIX_NONE;

  if(arg.size() >= 2 && arg[0] == '-') {
    prefix = ARGUMENT_PREFIX_SHORT;
    if(arg.size() >= 3 && arg[1] == '-') {
      prefix = ARGUMENT_PREFIX_LONG;
    }
  }

  std::string argument(arg.substr(prefix));

  if(prefix == ARGUMENT_PREFIX_LONG) {
    parseLongArg(argument);
  } else if(prefix == ARGUMENT_PREFIX_SHORT) {
    for(int i=0; i<argument.size(); i++) {
      parseShortArg(argument.c_str()[i]);
    }
  } else {
    log(LOG_LEVEL_VOMIT, "argument: " + argument);
  }

  return ARGUMENT_PARSE_MODE_ARGS;
}

ArgumentParseMode Program::parseShortArg(char arg) {
  switch(arg) {
   case 'h':
     this->hasFlag(ARGUMENT_FLAG_HELP);
     break;
   case 'v':
     this->hasFlag(ARGUMENT_FLAG_LOG_LEVEL, false);
     break;
   case 'q':
     this->hasFlag(ARGUMENT_FLAG_LOG_LEVEL, true);
     break;
   default:
     throw invalid_argument_exception(ARGUMENT_PREFIX_SHORT, std::string(1, arg));
     break;
  }
}

ArgumentParseMode Program::parseLongArg(std::string arg) {
  if(arg == "help") {
    this->hasFlag(ARGUMENT_FLAG_HELP);
  } else if(arg == "version") {
    this->hasFlag(ARGUMENT_FLAG_VERSION);
  } else if(arg == "vomit") {
    this->hasFlag(ARGUMENT_FLAG_LOG_LEVEL, LOG_LEVEL_VOMIT);
  } else if(arg == "verbose") {
    this->hasFlag(ARGUMENT_FLAG_LOG_LEVEL, LOG_LEVEL_DEBUG);
  } else if(arg == "quiet") {
    this->hasFlag(ARGUMENT_FLAG_LOG_LEVEL, LOG_LEVEL_WARN);
  } else if(arg == "silent") {
    this->hasFlag(ARGUMENT_FLAG_LOG_LEVEL, LOG_LEVEL_FATAL);
  } else if(arg == "no-colors") {
    this->hasFlag(ARGUMENT_FLAG_LOG_COLOR, false);
  } else {
    throw invalid_argument_exception(ARGUMENT_PREFIX_LONG, arg);
  }
}

// FLAGS

void Program::hasFlag(ArgumentFlag flag, bool value) {

  int offset = 1;
  if(!value) offset = -1;

  switch(flag) {
   case ARGUMENT_FLAG_HELP:
     this->help = true;
     break;
   case ARGUMENT_FLAG_VERSION:
     this->version = true;
     break;
   case ARGUMENT_FLAG_LOG_COLOR:
     this->log_use_colors = value;
     break;
   case ARGUMENT_FLAG_LOG_LEVEL:
     this->log_level = clamp(this->log_level + offset, 0, LOG_LEVEL_MAX - 1);
     break;
   default:
     log(LOG_LEVEL_INTERNAL, "got an unknown flag in hasFlag(flag, bool)");
     break;
  }

}

void Program::hasFlag(ArgumentFlag flag, int value) {

  switch(flag) {
   case ARGUMENT_FLAG_LOG_LEVEL:
     this->log_level = clamp(value, 0, LOG_LEVEL_MAX - 1);
     break;
   default:
     log(LOG_LEVEL_INTERNAL, "got an unknown flag in hasFlag(flag, int)");
     break;
  }

}

void Program::hasFlag(ArgumentFlag flag) {
  this->hasFlag(flag, true);
}

// HELP

void Program::displayHelp(bool force) {
  log(LOG_LEVEL_INFO, "", force);
  log(LOG_LEVEL_INFO, "Usage: " + this->args[0] + " [OPTIONS]", force);
  log(LOG_LEVEL_INFO, "", force);
  log(LOG_LEVEL_INFO, "General options:", force);
  log(LOG_LEVEL_INFO, "    -h  --help                    Display this help", force);
  log(LOG_LEVEL_INFO, "        --version                 Display the version of pFlight", force);
  log(LOG_LEVEL_INFO, "", force);
  log(LOG_LEVEL_INFO, "Logging options:", force);
  log(LOG_LEVEL_INFO, "    -q                            Display less log output", force);
  log(LOG_LEVEL_INFO, "    -v                            Display more log output", force);
  log(LOG_LEVEL_INFO, "        --silent                  Log only during fatal errors", force);
  log(LOG_LEVEL_INFO, "        --quiet                   Log only warnings and up", force);
  log(LOG_LEVEL_INFO, "        --verbose                 Log only debug messages and up", force);
  log(LOG_LEVEL_INFO, "        --vomit                   Log EVERYTHING", force);
  log(LOG_LEVEL_INFO, "", force);
  log(LOG_LEVEL_INFO, "Config options:", force);
  log(LOG_LEVEL_INFO, "    -c  --config <filename>       Read custom config file", force);
  log(LOG_LEVEL_INFO, "        --no-default-config       Do not read system-wide and user config; same\
 as --no-system-config --no-user-config", force);
  log(LOG_LEVEL_INFO, "        --no-system-config        Do not read system-wide config file", force);
  log(LOG_LEVEL_INFO, "        --no-user-config          Do not read user config file", force);
  log(LOG_LEVEL_INFO, "", force);
}

void Program::displayVersion(bool force) {
  log(LOG_LEVEL_INFO, " pFlight version " + std::string(PFLIGHT_VERSION), force);
}
