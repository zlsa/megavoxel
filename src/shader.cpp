
#include <GL/glew.h>

#include "shader.hpp"

#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "util.hpp"
#include "log.hpp"

Shader::Shader() {
#if LOG_SCENEGRAPH_CHANGES
  log(LOG_LEVEL_DUMP, "creating Shader");
#endif
  
  this->create();

  this->state = SHADER_STATE_NOT_READY;
}

Shader::~Shader() {

#if !MEGAVOXEL_HEADLESS
  if(this->program != 0)
    glDeleteProgram(this->program);

  if(this->vertex_shader != 0)
    glDeleteShader(this->vertex_shader);
  
  if(this->fragment_shader != 0)
    glDeleteShader(this->fragment_shader);
#endif
  
  log(LOG_LEVEL_DUMP, "deleting Shader '" + this->getName() + "'");
}

void Shader::create() {
  this->setName("unnamed Shader");
}

void Shader::createShader(std::string vertex_filename, std::string fragment_filename) {
  std::string contents = readDataFile(DATA_DIRECTORY_SHADERS, vertex_filename);

  if(!this->createVertexShaderFromString(contents, vertex_filename)) {
    return;
  }

  contents = readDataFile(DATA_DIRECTORY_SHADERS, fragment_filename);
  
  if(!this->createFragmentShaderFromString(contents, fragment_filename)) {
    return;
  }

  if(!this->createProgram()) {
    return;
  }

  this->state = SHADER_STATE_READY;
  
}

bool Shader::createProgram() {
#if !MEGAVOXEL_HEADLESS
  this->program = glCreateProgram();

  glAttachShader(this->program, this->vertex_shader);
  glAttachShader(this->program, this->fragment_shader);
  
  glLinkProgram(this->program);

  GLint status;
	glGetProgramiv(this->program, GL_LINK_STATUS, &status);
  
	if(status == GL_FALSE) {
		int program_log_length;
    glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &program_log_length);
    
		GLchar program_log[program_log_length];
    glGetProgramInfoLog(this->program, program_log_length, &program_log_length, program_log);

    // Remove the trailing newline.
    program_log[program_log_length-1] = '\0';

    log(LOG_LEVEL_WARN, "couldn't link shader program");
    
    log(LOG_LEVEL_WARN, std::string(program_log));

    log(LOG_LEVEL_WARN, "aborting shader creation");
    
    glDeleteProgram(this->program);

    this->program = 0;
    
    return false;
	}
#endif
  
  return true;
}

bool Shader::createVertexShaderFromString(std::string contents, std::string filename) {
  this->vertex_shader = this->createShaderFromString(GL_VERTEX_SHADER, contents, filename);

  return this->vertex_shader != 0;
}

bool Shader::createFragmentShaderFromString(std::string contents, std::string filename) {
  this->fragment_shader = this->createShaderFromString(GL_FRAGMENT_SHADER, contents, filename);
  
  return this->vertex_shader != 0;
}

int Shader::createShaderFromString(GLenum type, std::string contents, std::string filename) {
  
  if(contents.length() == 0) {
    log(LOG_LEVEL_WARN, "no shader in " + filename+ "; aborting shader creation");
    return 0;
  }

#if !MEGAVOXEL_HEADLESS
  GLint shader = glCreateShader(type);

  const char *c_str = contents.c_str();
  glShaderSource(shader, 1, &c_str, NULL);

  glCompileShader(shader);

  // Error handling.

  GLint success = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if(success == GL_FALSE) {
    log(LOG_LEVEL_WARN, "couldn't compile shader '" + filename + "'");

    GLint shader_log_length = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &shader_log_length);

    GLchar shader_log[shader_log_length];
    glGetShaderInfoLog(shader, shader_log_length, &shader_log_length, shader_log);

    // Remove the trailing newline.
    shader_log[shader_log_length-1] = '\0';

    log(LOG_LEVEL_WARN, std::string(shader_log));

    log(LOG_LEVEL_WARN, "aborting shader creation");
    
    glDeleteShader(shader);

    return 0;
  }
  
  return shader;
#endif

  return 1;
  
}

GLint Shader::getUniformLocation(std::string name) {
#if !MEGAVOXEL_HEADLESS
  
  GLint location = glGetUniformLocation(this->program, name.c_str());
  
  if(location < 0) {
    //log(LOG_LEVEL_WARN, "no such uniform '" + name + "' in shader '" + this->getName() + "'");
  } else {
    //log(LOG_LEVEL_WARN, "uniform named '" + name + "' is " + std::to_string(location));
  }

  return location;
#endif
  return 1;
}

GLint Shader::getAttributeLocation(std::string name) {
#if !MEGAVOXEL_HEADLESS
  
  GLint location = glGetAttribLocation(this->program, name.c_str());
  
  if(location < 0) {
    //log(LOG_LEVEL_WARN, "no such attribute '" + name + "' in shader '" + this->getName() + "'");
  } else {
    //log(LOG_LEVEL_WARN, "uniform named '" + name + "' is " + std::to_string(location));
  }

  return location;
#endif
  return 1;
}

void Shader::bind() {
  assert(this->state == SHADER_STATE_READY);

#if !MEGAVOXEL_HEADLESS
  glUseProgram(this->program);
#endif
  
}
