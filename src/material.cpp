
#include "material.hpp"

#include "log.hpp"

Material::Material() {
#if LOG_SCENEGRAPH_CHANGES
  log(LOG_LEVEL_DUMP, "creating Material");
#endif
  
  this->setName("unnamed Material");
  
  this->shader = NULL;
}

Material::~Material() {
  log(LOG_LEVEL_DUMP, "deleting Material '" + this->getName() + "'");

  if(this->shader != NULL)
    this->shader->unuse();
}

void Material::setShader(Shader *shader) {
  assert(shader);
    
  shader->use();
  
  if(this->shader != NULL)
    this->shader->unuse();
  
  this->shader = shader;
}

Shader *Material::getShader() {
  return this->shader;
}

void Material::bind() {
  this->shader->bind();
}
