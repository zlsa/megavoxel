
#include "program.hpp"
#include "util.hpp"
#include <algorithm>
#include <cctype>

#include <GL/glew.h>
#include "log.hpp"

extern Program *program;

double clamp(double n, double lower, double upper) {
  return(std::max(lower, std::min(n, upper)));
}

int clamp(int n, int lower, int upper) {
  return(std::max(lower, std::min(n, upper)));
}

std::string bool_to_string(bool value) {
  if(value) return("true");
  return("false");
}

std::string vector_to_string(std::vector<std::string> vector) {
  std::string s;
  int i = 0;
  s += "[";
  for(auto item : vector) {
    if(i > 0) s += ", ";
    s += item;
    i += 1;
  }
  s += "]";
  return(s);
}

std::string vector_to_string(std::vector<boost::filesystem::path> vector) {
  std::string s;
  int i = 0;
  s += "[";
  for(auto item : vector) {
    if(i > 0) s += ", ";
    s += item.string();
    i += 1;
  }
  s += "]";
  return(s);
}

std::string plural(int value, std::string single, std::string other) {
  if(value == 1) return single;
  return other;
}

std::string plural(float value, std::string single, std::string other) {
  if(value == 1.0) return single;
  return other;
}

// file io

std::string readFile(std::string filename) {
  std::ifstream file;

  file.open(filename);

  if(!file.is_open()) {
    log(LOG_LEVEL_WARN, "could not read from '" + filename + "'");
    return "";
  }
  
  std::string content;

  file.seekg(0, std::ios::end);   
  content.reserve(file.tellg());
  file.seekg(0, std::ios::beg);

  content.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

  return content;
}

std::string readDataFile(std::string directory, std::string filename) {
  std::string data_directory = DATA_DIRECTORY;

  if(program != NULL) {
    data_directory = program->getConfig()->getStringValue("data_directory", DATA_DIRECTORY);
    
    log(LOG_LEVEL_DUMP, "using custom data directory " + data_directory);
  }
  
  boost::filesystem::path dir(data_directory / boost::filesystem::path(directory));
  boost::filesystem::path path(dir / boost::filesystem::path(filename));

  log(LOG_LEVEL_DUMP, "reading data file " + path.string());
  
  return readFile(path.string());
}

void checkGlError() {
  GLenum error = glGetError();

  switch(error) {
   case GL_NO_ERROR:
     return;
   case GL_INVALID_ENUM:
     log_internal("uncaught OpenGL error GL_INVALID_ENUM");
     return;
   case GL_INVALID_VALUE:
     log_internal("uncaught OpenGL error GL_INVALID_VALUE");
     return;
   case GL_INVALID_OPERATION:
     log_internal("uncaught OpenGL error GL_INVALID_OPERATION");
     return;
   case GL_INVALID_FRAMEBUFFER_OPERATION:
     log_internal("uncaught OpenGL error GL_INVALID_FRAMEBUFFER_OPERATION");
     return;
   case GL_OUT_OF_MEMORY:
     log(LOG_LEVEL_FATAL, "OpenGL reports out of memory");
     return;
  }
}
