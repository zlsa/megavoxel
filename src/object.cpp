
#include "object.hpp"

#include "log.hpp"

Object::Object() {
  this->type   = OBJECT_TYPE_NONE;

  this->setName("unnamed Object");
  
  this->parent = NULL;
  this->matrix = glm::mat4(1.0);
  this->mesh   = NULL;
  this->camera = NULL;
}

void Object::deleteSelf() {
  for(Object *object : this->children) {
    this->remove(object);
  }
  this->deleteData();
  log(LOG_LEVEL_DUMP, "deleting Object '" + this->getName() + "'");
}

void Object::deleteData() {
  if(this->mesh)
    this->mesh->unuse();
  // TODO add all types here
}

glm::vec3 Object::getPosition() {
  return(glm::vec3(this->matrix[3]));
}

void Object::setType(ObjectType type) {
  this->type = type;
}

void Object::setMesh(Mesh *mesh) {
  assert(this->type == OBJECT_TYPE_MESH);
  assert(mesh);
  
  Mesh *temp = this->mesh;
  
  if(mesh != NULL) {
    this->mesh = mesh;
    mesh->use();
  }
  
  if(temp) temp->unuse();
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
  log(LOG_LEVEL_DUMP, "parenting '" + this->getName() + "' to '" + object->getName() + "'");
  Object *temp = this->parent;
  this->parent = object;
  
  if(temp != NULL) temp->remove(this);
}

void Object::remove(Object *object) {
  assert(object);
  
  if(this->children.find(object) == this->children.end()) {
    log(LOG_LEVEL_DUMP, "removing '" + object->getName() + "' from '" + this->getName() + "'");
    object->unuse();
    this->children.erase(object);
  }
  
}

void Object::add(Object *object) {
  assert(object);
  log(LOG_LEVEL_DUMP, "adding '" + object->getName() + "' to '" + this->getName() + "'");
  object->setParent(this);
  this->children.insert(object);
  object->use();
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
