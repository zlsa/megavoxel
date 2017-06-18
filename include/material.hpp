
#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include "shader.hpp"
#include "datablock.hpp"

class Material: public Datablock {
 protected:
  Shader *shader;
  
 public:
  Material();

  void setShader(Shader *shader);
  Shader *getShader();

  void bind();
};

#endif
