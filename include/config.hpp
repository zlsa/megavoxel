
#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <unordered_map>

#include "pflight_config.hpp"

#ifdef __linux
#define CONFIG_SYSTEM_PATH SYSTEM_PREFIX "/share/pflight/config"
#else
#define CONFIG_SYSTEM_PATH SYSTEM_PREFIX "config"
#endif

enum ConfigSource {
  CONFIG_SOURCE_NONE = 0,
  CONFIG_SOURCE_DEFAULT,
  CONFIG_SOURCE_SYSTEM,
  CONFIG_SOURCE_USER,
  CONFIG_SOURCE_RUNTIME
};

enum ConfigType {
  CONFIG_TYPE_NONE = 0,
  CONFIG_TYPE_INT,
  CONFIG_TYPE_DOUBLE,
  CONFIG_TYPE_STRING,
  CONFIG_TYPE_PATH
};

class ConfigValue {
  
 protected:
  ConfigType type;

  int int_value;
  double double_value;
  std::string string_value;
  std::vector<boost::filesystem::path> path_value;
  
 public:
  ConfigValue();
};

class ConfigItem {
  
 protected:
  std::string key;
  ConfigValue value;
  
  ConfigSource source;
  
 public:
  ConfigItem();
};

class Config {
 protected:
  std::unordered_map<std::string, ConfigItem> keys;

 public:
  void parseConfigFile(boost::filesystem::path path);
  void parseSystemConfig();
};

#endif
