
#include "object.hpp"

Object::Object() {
  this->matrix = glm::mat4(1.0);
  this->mesh   = NULL;
}

glm::vec3 Object::getPosition() {
  return(glm::vec3(this->matrix[3]));
}

void Object::setMesh(Mesh *mesh) {
  if(this->mesh) this->mesh->unuse();
  
  if(mesh != NULL) {
    this->mesh = mesh;
    mesh->use();
  }
}

// matrix stuff

glm::mat4 Object::getMatrix(bool world) {
  if(world) return this->world_matrix;
  else      return this->matrix;
}

void Object::updateMatrix() {
  if(!this->parent)
    this->world_matrix = this->matrix;
  else
    this->world_matrix = this->parent->getMatrix() * this->matrix;
}

// parenting

void Object::setParent(Object *object) {
  if(this->parent) this->parent->remove(this);
  this->parent = object;
}

void Object::remove(Object *object) {
  // TODO: check for existence first
  this->children.erase(object);
}

void Object::add(Object *object) {
  object->setParent(this);
  this->children.insert(object);
}

// draw

void Object::drawMesh() {
}

void Object::drawChildren() {
  for(Object *child : this->children) {
    child->draw();
  }
}

void Object::draw() {
  this->drawMesh();
  this->drawChildren();
}
