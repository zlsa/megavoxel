
#ifndef SHADER_H
#define SHADER_H

class Shader {
 protected:

 public:
  Shader();
  Shader(std::string vertex_filename, std::string fragment_filename);
  void create();

  void loadVertexShader(std::string filename);
}

#endif
