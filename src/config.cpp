
#include "config.hpp"

#include <iostream>
#include <locale>
#include <boost/algorithm/string.hpp>

#include "util.hpp"
#include "log.hpp"

////////////////////////////////////////////////////////////////////////////////
// CONFIGVALUE
////////////////////////////////////////////////////////////////////////////////

ConfigValue::ConfigValue() {
  
}

void ConfigValue::setType(ConfigType type) {
  this->type = type;
}

void ConfigValue::setValue(bool value) {
  this->bool_value = value;
}

void ConfigValue::setValue(int value) {
  this->int_value = value;
}

void ConfigValue::setValue(double value) {
  this->double_value = value;
}

void ConfigValue::setValue(std::string value) {
  this->string_value = value;
}

void ConfigValue::setValue(boost::filesystem::path value) {
  this->path_value.push_back(value);
}

void ConfigValue::setValueAuto(std::string value) {
  switch(this->type) {
   case CONFIG_TYPE_BOOL:
     if(value == "true" || value == "1" || value == "on") {
       this->setValue(true);
     } else if(value == "false" || value == "0" || value == "off") {
       this->setValue(false);
     } else {
       throw invalid_value_exception(this->type, value);
     }
     break;
   case CONFIG_TYPE_INT:
     try {
       this->setValue(std::stoi(value));
     } catch(std::exception e) {
       throw invalid_value_exception(this->type, value);
     }
     break;
   case CONFIG_TYPE_DOUBLE:
     try {
       this->setValue(std::stod(value));
     } catch(std::exception e) {
       throw invalid_value_exception(this->type, value);
     }
     break;
   case CONFIG_TYPE_STRING:
     this->setValue(value);
     break;
   case CONFIG_TYPE_PATH:
     this->setValue(boost::filesystem::path(value));
     break;
   default:
     throw invalid_value_exception(this->type, value);
  }
}

ConfigType ConfigValue::getType() {
  return(this->type);
}

////////////////////////////////////////////////////////////////////////////////
// CONFIGITEM
////////////////////////////////////////////////////////////////////////////////

ConfigItem::ConfigItem() {
  
}

void ConfigItem::setType(ConfigType type) {
  this->value.setType(type);
}

void ConfigItem::setKey(std::string key) {
  this->key = key;
}

void ConfigItem::setValue(bool value) {
  this->value.setValue(value);
}

void ConfigItem::setValue(int value) {
  this->value.setValue(value);
}

void ConfigItem::setValue(double value) {
  this->value.setValue(value);
}

void ConfigItem::setValue(std::string value) {
  this->value.setValue(value);
}

void ConfigItem::setValue(boost::filesystem::path value) {
  this->value.setValue(value);
}

void ConfigItem::setValueAuto(std::string value) {
  this->value.setValueAuto(value);
}

void ConfigItem::dump() {
  log(LOG_LEVEL_DUMP, CONFIG_TYPE(this->value.getType()) + std::string(" ") + this->key + ";");
}

////////////////////////////////////////////////////////////////////////////////
// CONFIG
////////////////////////////////////////////////////////////////////////////////

ConfigItem *Config::readConfigLine(std::string line, std::string filename, int line_number) {
  if(line.size() == 0) return(NULL);
  if(line.size() >= 1 && line[0] == '#') return(NULL);
  if(line.size() >= 2 && line[0] == '/' && line[1] == '/') return(NULL);

  ConfigLineState state = CONFIG_STATE_WAIT_TYPE;
  bool skipping_whitespace = true;

  ConfigType type;
  std::string key;
  std::string value;

  std::string buffer;

  bool in_string = false;

  char c;
  int i;
  for(i=0; i<line.size(); i++) {
    c = line[i];
    
    if(
      (isspace(c) ||
       (state == CONFIG_STATE_WAIT_EQUALS && buffer.size() == 1) || 
       (state == CONFIG_STATE_WAIT_VALUE && c == ';')
        ) && !in_string) {

      if(!skipping_whitespace) {
        switch(state) {
         case CONFIG_STATE_WAIT_TYPE:
           if((type = convertStringToType(buffer)) == CONFIG_TYPE_NONE) {
             log(LOG_LEVEL_WARN, "invalid type '" + buffer + "'" CONFIG_FILE_INFO(filename, line_number));
             return(NULL);
           }
           state = CONFIG_STATE_WAIT_KEY;
           break;
         case CONFIG_STATE_WAIT_KEY:
           if(!isValidKey(buffer)) {
             log(LOG_LEVEL_WARN, "invalid key '" + buffer + "'" CONFIG_FILE_INFO(filename, line_number));
             return(NULL);
           }
           key = buffer;
           state = CONFIG_STATE_WAIT_EQUALS;
           break;
         case CONFIG_STATE_WAIT_EQUALS:
           if(buffer != "=") {
             log(LOG_LEVEL_WARN, "expected equals sign" CONFIG_FILE_INFO(filename, line_number));
             return(NULL);
           }
           state = CONFIG_STATE_WAIT_VALUE;
           break;
         case CONFIG_STATE_WAIT_VALUE:
           value = buffer;
           state = CONFIG_STATE_WAIT_SEMICOLON;
           break;
         case CONFIG_STATE_WAIT_SEMICOLON:
           if(buffer != ";") {
             log(LOG_LEVEL_WARN, "expected terminating semicolon" CONFIG_FILE_INFO(filename, line_number));
             log(LOG_LEVEL_DUMP, buffer);
             return(NULL);
           }
           state = CONFIG_STATE_WAIT_NEWLINE;
           break;
        }

        buffer = "";
        skipping_whitespace = true;
      }
      
      continue;
    }

    skipping_whitespace = false;
    if(state == CONFIG_STATE_WAIT_VALUE) {
      if(type == CONFIG_TYPE_STRING) {
        if(c == '"') {
          if(!in_string) {
            in_string = true;
            continue;
          } else {
            in_string = false;
            state = CONFIG_STATE_WAIT_SEMICOLON;
            value = buffer;
            buffer = "";
            continue;
          }
        }
      }
    }
    buffer += c;

  }

  if(state <= CONFIG_STATE_WAIT_VALUE) {
    log(LOG_LEVEL_WARN, "incomplete configuration item" CONFIG_FILE_INFO(filename, line_number));
    return(NULL);
  }

  ConfigItem *item = new ConfigItem();
  try {
    item->setType(type);
    item->setKey(key);
    item->setValueAuto(value);
  } catch(invalid_value_exception e) {
    log(LOG_LEVEL_WARN, "invalid value '" + e.value + "'" CONFIG_FILE_INFO(filename, line_number));
  }

  return(item);

}

void Config::addItem(ConfigItem *item) {
  if(item != NULL)
    this->items.push_back(item);
}

int Config::readConfigFile(std::ifstream *file, std::string filename) {
  
  std::string line;

  int lines = 0;
  
  while(getline(*file, line) ) {
    boost::algorithm::trim(line);
    this->addItem(this->readConfigLine(line, filename, lines));
    lines += 1;
  }

  return(lines);
  
}

void Config::parseConfigFile(boost::filesystem::path path) {

  std::string filename = path.string();

  if(!boost::filesystem::exists(path)) {
    log(LOG_LEVEL_WARN, "could not open config file '" + filename + "' for reading");
    return;
  }

  if(!boost::filesystem::is_regular_file(path)) {
    log(LOG_LEVEL_WARN, "config file '" + filename + "' is not a regular file");
    return;
  }

  std::ifstream *file = new std::ifstream(filename, std::ios::in);

  if(file->is_open()) {
    log(LOG_LEVEL_DEBUG, "parsing '" + filename + "'");
    int lines = this->readConfigFile(file, filename);
    file->close();
    log(LOG_LEVEL_DEBUG, "parsed " + std::to_string(lines) + " line" + plural(lines) + " of '" + filename + "'");
  } else {
    log(LOG_LEVEL_WARN, "could not open config file '" + filename + "'");
  }
  
  delete file;
}

void Config::parseSystemConfig() {
  this->parseConfigFile(boost::filesystem::path(CONFIG_SYSTEM_PATH));
}

void Config::parseUserConfig() {
  boost::filesystem::path config_user_directory(CONFIG_USER_DIRECTORY);
  boost::filesystem::path config_user_path(CONFIG_USER_PATH);
  
  if(!boost::filesystem::exists(config_user_path.string())) {
    boost::filesystem::create_directories(config_user_directory.string());
    
    log(LOG_LEVEL_NOTICE, "created config directory '" + config_user_directory.string() + "'");
      
    std::ofstream outfile(config_user_path.string());
    outfile << "// created by pflight" << std::endl;
    outfile.close();
      
    log(LOG_LEVEL_NOTICE, "created user config file '" + config_user_path.string() + "'");
  }
  
  this->parseConfigFile(boost::filesystem::path(config_user_path));
}

// DEBUG

void Config::dump() {
  log(LOG_LEVEL_DUMP, " -- dumping Config  -- ");
  for(int i=0; i<this->items.size(); i++) {
    this->items[i]->dump();
  }
  log(LOG_LEVEL_DUMP, " --   end Config    -- ");
}

// DESTRUCTOR

Config::~Config() {
  log(LOG_LEVEL_DUMP, "deleting Config");
}

// HELPER FUNCTIONS

ConfigType convertStringToType(std::string type) {
  boost::algorithm::to_lower(type);
  if     (type == "bool")    return(CONFIG_TYPE_BOOL);
  else if(type == "int")     return(CONFIG_TYPE_INT);
  else if(type == "double")  return(CONFIG_TYPE_DOUBLE);
  else if(type == "string")  return(CONFIG_TYPE_STRING);
  else if(type == "path")    return(CONFIG_TYPE_PATH);
  return(CONFIG_TYPE_NONE);
}

bool isValidKey(std::string key) {
  std::locale locale;
  if(key.size() < 1) {
    return(false);
  }
  int i=0;
  for (std::string::iterator it=key.begin(); it!=key.end(); ++it) {
    if((!isalpha(*it, locale) || (i == 0 && isdigit(*it))) && (*it != '_')) {
      return(false);
    }
    i++;
  }
  return(true);
}

