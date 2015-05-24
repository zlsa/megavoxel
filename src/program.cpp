
#include <iostream>

#include "pflight_config.hpp"

#include "program.hpp"
#include "util.hpp"
#include "log.hpp"

Program::Program(int argc, char *argv[]) {
  this->args.assign(argv, argv + argc);

  this->config_use_system = true;
  this->config_use_user   = true;

  this->config            = new Config();
  
  this->value_flag        = ARGUMENT_FLAG_NONE;

  this->log_level         = LOG_LEVEL_INFO;
  this->log_use_colors    = true;

  this->should_exit       = false;
}

void Program::parseArgs() {

  ArgumentParseMode mode = ARGUMENT_PARSE_MODE_ARGS;

  bool invalid = false;
  std::string invalid_argument;
  ArgumentPrefix invalid_prefix = ARGUMENT_PREFIX_NONE;

  for(int i=1; i<this->args.size(); i++) {
    try {
      this->parseArg(this->args[i]);

      if(this->value_flag != ARGUMENT_FLAG_NONE) {
        if(i > this->args.size() - 2) {
          throw invalid_argument_exception(ARGUMENT_PREFIX_VALUE, this->args[i]);
        }
        i += 1;
        if(this->value_flag == ARGUMENT_FLAG_CONFIG_EXTRA) {
          this->parseArgValue(this->value_flag, this->args[i]);
        }
      }
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
      log(LOG_LEVEL_FATAL, "invalid short argument '" + invalid_argument + "'");
    } else if(invalid_prefix == ARGUMENT_PREFIX_LONG) {
      log(LOG_LEVEL_FATAL, "invalid long argument '" + invalid_argument + "'");
    } else if(invalid_prefix == ARGUMENT_PREFIX_VALUE) {
      log(LOG_LEVEL_FATAL, "expected a value after '" + invalid_argument + "'");
    } else {
      log(LOG_LEVEL_FATAL, "did not expect value '" + invalid_argument + "'");
    }
  }

  log(LOG_LEVEL_DUMP, "log level: " + std::to_string(this->log_level));
  
}

void Program::parseArg(std::string arg) {
  ArgumentPrefix prefix = ARGUMENT_PREFIX_NONE;

  this->value_flag = ARGUMENT_FLAG_NONE;
  
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
    log(LOG_LEVEL_DUMP, "argument: " + argument);
    log(LOG_LEVEL_DUMP, "argument: " + argument);
    throw invalid_argument_exception(prefix, argument);
  }

}

void Program::parseShortArg(char arg) {
  if(this->value_flag != ARGUMENT_FLAG_NONE) {
    throw invalid_argument_exception(ARGUMENT_PREFIX_SHORT, std::string(1, arg));
  }
  switch(arg) {
   case 'h':
     this->setFlag(ARGUMENT_FLAG_HELP);
     break;
   case 'v':
     this->setFlag(ARGUMENT_FLAG_LOG_LEVEL, false);
     break;
   case 'q':
     this->setFlag(ARGUMENT_FLAG_LOG_LEVEL, true);
     break;
   case 'c':
     this->value_flag = ARGUMENT_FLAG_CONFIG_EXTRA;
     break;
   default:
     throw invalid_argument_exception(ARGUMENT_PREFIX_SHORT, std::string(1, arg));
     break;
  }
}

void Program::parseLongArg(std::string arg) {
  if(arg == "help") {
    this->setFlag(ARGUMENT_FLAG_HELP);
  } else if(arg == "version") {
    this->setFlag(ARGUMENT_FLAG_VERSION);
  } else if(arg == "dump") {
    this->setFlag(ARGUMENT_FLAG_LOG_LEVEL, LOG_LEVEL_DUMP);
  } else if(arg == "debug") {
    this->setFlag(ARGUMENT_FLAG_LOG_LEVEL, LOG_LEVEL_DEBUG);
  } else if(arg == "quiet") {
    this->setFlag(ARGUMENT_FLAG_LOG_LEVEL, LOG_LEVEL_WARN);
  } else if(arg == "silent") {
    this->setFlag(ARGUMENT_FLAG_LOG_LEVEL, LOG_LEVEL_FATAL);
  } else if(arg == "no-colors") {
    this->setFlag(ARGUMENT_FLAG_LOG_COLOR, false);
  } else if(arg == "no-default-config") {
    this->setFlag(ARGUMENT_FLAG_CONFIG_USE_SYSTEM, false);
    this->setFlag(ARGUMENT_FLAG_CONFIG_USE_USER, false);
  } else if(arg == "no-system-config") {
    this->setFlag(ARGUMENT_FLAG_CONFIG_USE_SYSTEM, false);
  } else if(arg == "no-user-config") {
    this->setFlag(ARGUMENT_FLAG_CONFIG_USE_USER, false);
  } else if(arg == "config") {
    this->value_flag = ARGUMENT_FLAG_CONFIG_EXTRA;
  } else {
    throw invalid_argument_exception(ARGUMENT_PREFIX_LONG, arg);
  }
}

void Program::parseArgValue(ArgumentFlag flag, std::string value) {
  this->setFlag(flag, value);
}

// FLAGS

void Program::setFlag(ArgumentFlag flag, bool value) {

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
   case ARGUMENT_FLAG_CONFIG_USE_SYSTEM:
     this->config_use_system = value;
     break;
   case ARGUMENT_FLAG_CONFIG_USE_USER:
     this->config_use_user = value;
     break;
   default:
     log(LOG_LEVEL_INTERNAL, "got an unknown flag in setFlag(flag, bool)");
     break;
  }

}

void Program::setFlag(ArgumentFlag flag, int value) {

  switch(flag) {
   case ARGUMENT_FLAG_LOG_LEVEL:
     this->log_level = clamp(value, 0, LOG_LEVEL_MAX - 1);
     break;
   default:
     log(LOG_LEVEL_INTERNAL, "got an unknown flag in setFlag(flag, int)");
     break;
  }

}

void Program::setFlag(ArgumentFlag flag, std::string value) {

  switch(flag) {
   case ARGUMENT_FLAG_CONFIG_EXTRA:
     log(LOG_LEVEL_DEBUG, "added config file '" + value + "'");
     this->config_extra.push_back(boost::filesystem::path(value));
     break;
   default:
     log(LOG_LEVEL_INTERNAL, "got an unknown flag in setFlag(flag, std::string)");
     break;
  }

}

void Program::setFlag(ArgumentFlag flag) {
  this->setFlag(flag, true);
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
  log(LOG_LEVEL_INFO, "        --no-colors               Do not use colors when printing to terminal", force);
  log(LOG_LEVEL_INFO, "    -q                            Display less log output", force);
  log(LOG_LEVEL_INFO, "    -v                            Display more log output", force);
  log(LOG_LEVEL_INFO, "        --silent                  Log only during fatal errors", force);
  log(LOG_LEVEL_INFO, "        --quiet                   Log only warnings and up", force);
  log(LOG_LEVEL_INFO, "        --debug                   Log only debug messages and up", force);
  log(LOG_LEVEL_INFO, "        --dump                    Log EVERYTHING", force);
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
  log(LOG_LEVEL_INFO, "pFlight version " + std::string(PFLIGHT_VERSION), force);
}

// CONFIG

void Program::parseConfig() {
  if(this->config_use_system)
    this->config->parseSystemConfig();
  
  if(this->config_use_user)
    this->config->parseUserConfig();
  
  for(auto filename : this->config_extra) {
    this->config->parseConfigFile(filename);
  }
  
}

Config *Program::getConfig() {
  return(this->config);
}

// WINDOW

void Program::createWindow() {

  if(!glfwInit())
    log(LOG_LEVEL_FATAL, "could not initialize GLFW");
  
  this->window = new Window();
  
  int width = -1, height = -1;
  width  = this->config->getIntValue("window_width",  WINDOW_DEFAULT_WIDTH);
  height = this->config->getIntValue("window_height", WINDOW_DEFAULT_HEIGHT);
  
  this->window->setSize(width, height);
  this->window->create();
}

void Program::tick() {
  this->window->tick();
  this->should_exit = this->window->shouldClose();
}

bool Program::shouldExit() {
  return(this->should_exit);
}

// SCENE

Scene *Program::getScene() {
  return(&this->scene);
}

// DEBUG

void Program::dump() {
  log(LOG_LEVEL_DUMP, " -- dumping Program -- ");
  log(LOG_LEVEL_DUMP, "config_use_system         = " + bool_to_string(this->config_use_system));
  log(LOG_LEVEL_DUMP, "config_use_user           = " + bool_to_string(this->config_use_user));
  log(LOG_LEVEL_DUMP, "config_extra              = " + vector_to_string(this->config_extra));

  log(LOG_LEVEL_DUMP, "log_level                 = " + std::to_string(this->log_level));
  log(LOG_LEVEL_DUMP, "log_use_colors            = " + bool_to_string(this->log_use_colors));
  
  this->config->dump();
  
  log(LOG_LEVEL_DUMP, " --   end Program   -- ");
}

// DESTRUCTOR

Program::~Program() {
  glfwTerminate();
  delete this->window;
  delete this->config;
  log(LOG_LEVEL_DUMP, "deleting Program");
}
