
#include <GL/glew.h>

#include "shader.hpp"

#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "util.hpp"

Shader::Shader() {
  this->create();
}

Shader::Shader(std::string vertex_filename, std::string fragment_filename) {
  this->create();

  this->createShader(vertex_filename, fragment_filename);
}

void Shader::create() {
//  this->createVertexShader();
//  this->createProgram();
}

void Shader::createShader(std::string vertex_filename, std::string fragment_filename) {
  std::string contents = readFile(vertex_filename);
  this->createVertexShader(contents);
  
  contents = readFile(fragment_filename);
  this->createFragmentShader(contents);
  
  this->createProgram();
}

bool Shader::createProgram() {
  this->program = glCreateProgram();
  return(true);
}

bool Shader::createVertexShader(std::string contents) {
  this->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(this->vertex_shader, 1, (const GLchar**) contents.c_str(), 0);
  return(true);
}

bool Shader::createFragmentShader(std::string contents) {
  this->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(this->fragment_shader, 1, (const GLchar**) contents.c_str(), 0);
  return(true);
}

