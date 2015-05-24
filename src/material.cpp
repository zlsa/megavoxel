
#include "material.hpp"

Material::Material() {
  this->setName("unnamed Material");
  
  this->shader = NULL;
}

void Material::setShader(Shader *shader) {
  shader->use();
  
  if(this->shader != NULL) this->shader->unuse();
  
  this->shader = shader;
}
