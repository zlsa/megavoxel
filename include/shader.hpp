
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GLFW/glfw3.h>

#include "datablock.hpp"

enum ShaderState {
  SHADER_STATE_NOT_READY = 0,
  SHADER_STATE_READY = 0,
};

class Shader: public Datablock {
 protected:
  GLuint program;
  GLuint vertex_shader;
  GLuint fragment_shader;

  ShaderState state;

 public:
  Shader();
  Shader(std::string vertex_filename, std::string fragment_filename);
  void deleteSelf();
  
  void create();

  void createShader(std::string vertex_filename, std::string fragment_filename);
  bool createProgram();
  bool createVertexShader(std::string contents);
  bool createFragmentShader(std::string contents);
};

#endif
