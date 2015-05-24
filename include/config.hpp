
#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <fstream>

#include "pflight_config.hpp"

#ifdef __linux
#define CONFIG_SYSTEM_PATH SYSTEM_PREFIX "/share/pflight/config"
#define CONFIG_USER_DIRECTORY boost::filesystem::path(getenv("HOME")).string() + "/.pflight/"
#define CONFIG_USER_PATH CONFIG_USER_DIRECTORY "config"
#else
#endif

#define CONFIG_FILE_INFO(file, line) " on line " + std::to_string(line + 1) + " of '" + file + "'"

#define CONFIG_TYPE(t) (t == CONFIG_TYPE_BOOL ? "bool" : \
                        (t == CONFIG_TYPE_INT ? "int" : \
                         (t == CONFIG_TYPE_DOUBLE ? "double" : \
                          (t == CONFIG_TYPE_STRING ? "string" : \
                           (t == CONFIG_TYPE_PATH ? "path" : "none")))))

enum ConfigLineState {
  CONFIG_STATE_WAIT_TYPE,
  CONFIG_STATE_WAIT_KEY,
  CONFIG_STATE_WAIT_EQUALS,
  CONFIG_STATE_WAIT_VALUE,
  CONFIG_STATE_WAIT_SEMICOLON,
  CONFIG_STATE_WAIT_NEWLINE
};

enum ConfigSource {
  CONFIG_SOURCE_NONE = 0,
  CONFIG_SOURCE_DEFAULT,
  CONFIG_SOURCE_SYSTEM,
  CONFIG_SOURCE_USER,
  CONFIG_SOURCE_RUNTIME
};

enum ConfigType {
  CONFIG_TYPE_NONE = 0,
  CONFIG_TYPE_BOOL,
  CONFIG_TYPE_INT,
  CONFIG_TYPE_DOUBLE,
  CONFIG_TYPE_STRING,
  CONFIG_TYPE_PATH
};

class ConfigItem {
  
 protected:
  std::string key;

  ConfigType type;
  
  int bool_value;
  int int_value;
  double double_value;
  std::string string_value;
  std::vector<boost::filesystem::path> path_value;
  
  ConfigSource source;
  
 public:
  ConfigItem();
  ~ConfigItem();
  
  void setType(ConfigType type);
  void setKey(std::string key);
  void setValue(bool value);
  void setValue(int value);
  void setValue(double value);
  void setValue(std::string value);
  void setValue(boost::filesystem::path value);
  void setValueAuto(std::string value);

  std::string getKey();
  ConfigType getType();
  bool getBoolValue();
  int getIntValue();
  double getDoubleValue();
  std::string getStringValue();
  std::vector<boost::filesystem::path> getPathValue();
  std::string getAutoValue();
  
  // debugging
  void dump();
};

class Config {
 protected:
  std::vector<ConfigItem*> items;

 public:
  ~Config();
  ConfigItem *readConfigLine(std::string line, std::string filename, int line_number);
  int readConfigFile(std::ifstream *file, std::string filename);
  
  void addItem(ConfigItem *item);
  ConfigItem *getItem(std::string key);
  
  bool getBoolValue(std::string key, bool def=false);
  int getIntValue(std::string key, int def=0);
  double getDoubleValue(std::string key, double def=0.0);
  std::string getStringValue(std::string key, std::string def="");
  std::vector<boost::filesystem::path> getPathValue(std::string key);
  
  void parseConfigFile(boost::filesystem::path path);
  void parseSystemConfig();
  void parseUserConfig();

  // debugging
  void dump();
};

ConfigType convertStringToType(std::string type);
bool isValidKey(std::string key);

class invalid_value_exception: public std::exception {

 public:
  ConfigType type;
  std::string value;
  invalid_value_exception(ConfigType t, std::string val) : type(t), value(val) {};
  const char *what() const throw() { return value.c_str(); };
  
};

#endif
