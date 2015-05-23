
#include "config.hpp"

#include <iostream>

#include "log.hpp"

void Config::parseConfigFile(boost::filesystem::path path) {
  if(!boost::filesystem::exists(path)) {
    log(LOG_LEVEL_WARN, "could not open config file '" + path.string() + "' for reading");
    return;
  }

  if(!boost::filesystem::is_regular_file(path)) {
    log(LOG_LEVEL_WARN, "config file '" + path.string() + "' is not a regular file");
    return;
  }
  
}

void Config::parseSystemConfig() {
  this->parseConfigFile(boost::filesystem::path(CONFIG_SYSTEM_PATH));
}
