
#include "object.hpp"

Object::Object() {
  this->matrix = glm::mat4(1.0);
  this->mesh   = NULL;
}

void Object::setMesh(Mesh *mesh) {
  if(this->mesh) this->mesh->unuse();
  
  if(mesh != NULL) {
    this->mesh = mesh;
    mesh->use();
  }
}

glm::vec3 Object::getPosition() {
  return(glm::vec3(this->matrix[3]));
}

