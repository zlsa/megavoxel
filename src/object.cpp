
#include "object.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "log.hpp"

Object::Object() {
#if LOG_SCENEGRAPH_CHANGES
  log(LOG_LEVEL_DUMP, "creating Object");
#endif
  
  this->type   = OBJECT_TYPE_EMPTY;

  this->setName("unnamed Object");

  this->position = glm::vec3(0.0, 0.0, 0.0);
  this->scale = glm::vec3(1.0, 1.0, 1.0);
  this->matrix = glm::mat4(1.0);
  
  this->parent = NULL;
  this->data.mesh   = NULL;
  this->data.camera = NULL;
  this->scene  = NULL;

  this->visible = true;
  this->visible_self = true;
  this->visible_children = true;
}

Object::~Object() {
  
  //log(LOG_LEVEL_DUMP, "deleting Object '" + this->getName() + "'");

  // `parent` should *never* be non-null when this is called.
  assert(this->parent == NULL);

  for(Object *object : this->children) {
    object->unuse();
    
    //this->children.erase(object);
    
    //this->remove(object);
  }

  if(this->parent != NULL) {
    //this->parent->unuse();
  }
  
  this->deleteData();
}

void Object::deleteData() {
  
  if(this->type == OBJECT_TYPE_MESH && this->data.mesh != NULL)
    this->data.mesh->unuse();
  
  if(this->type == OBJECT_TYPE_CAMERA && this->data.camera != NULL)
    this->data.camera->unuse();
  
  // TODO add all types here
}

void Object::setPosition(glm::vec3 position) {
  this->position = position;
}

glm::vec3 Object::getPosition() {
  return this->position;
}

void Object::setScale(glm::vec3 scale) {
  this->scale = scale;
}

void Object::setScale(double scale) {
  this->scale = glm::vec3((float) scale, (float) scale, (float) scale);
}

glm::vec3 Object::getScale() {
  return this->scale;
}

void Object::setOrientation(glm::vec3 orientation) {
  this->orientation = glm::quat(orientation);
}

void Object::setOrientation(glm::quat orientation) {
  this->orientation = orientation;
}

glm::quat Object::getOrientation() {
  return this->orientation;
}

void Object::setType(ObjectType type) {
  this->type = type;
}

void Object::setMesh(Mesh *mesh) {
  assert(this->type == OBJECT_TYPE_MESH);
  assert(mesh);

  /*if(this->data.mesh != NULL)
    this->data.mesh->unuse();*/

  this->data.mesh = mesh;
  this->data.mesh->use();
  this->data.mesh->setObject(this);
}

void Object::setCamera(Camera *camera) {
  assert(this->type == OBJECT_TYPE_CAMERA);
  assert(camera);

  if(this->data.camera != NULL)
    this->data.camera->unuse();
  
  this->data.camera = camera;
  this->data.camera->use();
  this->data.camera->setObject(this);
}

Camera *Object::getCamera() {
  return this->data.camera;
}

// matrix stuff

glm::mat4 Object::getMatrix(bool world) {
  if(world) return this->world_matrix;
  else      return this->matrix;
}

void Object::updateMatrix() {
  this->matrix = glm::toMat4(this->orientation);
  this->matrix = glm::scale(this->matrix, this->scale);
  this->matrix = glm::translate(this->matrix, this->position);
  
  //this->matrix = glm::translate(glm::scale(glm::toMat4(this->orientation), this->scale), this->position);
    
  if(this->parent == NULL)
    this->world_matrix = this->matrix;
  else
    this->world_matrix = this->parent->getMatrix(true) * this->matrix;
}

// parenting

void Object::setParent(Object *object) {

#if LOG_SCENEGRAPH_CHANGES
  log(LOG_LEVEL_DUMP, "parenting '" + this->getName() + "' to '" + object->getName() + "'");
#endif

  Object *former_parent = this->parent;

  this->parent = object;

  //if(this->parent != NULL)
    //this->parent->use();
  
  //if(former_parent != NULL)
  //former_parent->unuse();

}

void Object::remove(Object *object) {
  assert(object);

  if(this->children.find(object) != this->children.end()) {
    
#if LOG_SCENEGRAPH_CHANGES
    log(LOG_LEVEL_DUMP, "removing child '" + object->getName() + "' from '" + this->getName() + "'");
#endif

    object->setParent(NULL);
    object->unuse();
    this->children.erase(object);
  }

}

void Object::add(Object *object) {
  assert(object);
  
#if LOG_SCENEGRAPH_CHANGES
  log(LOG_LEVEL_DUMP, "adding '" + object->getName() + "' to '" + this->getName() + "'");
#endif

  object->setParent(this);
  object->setScene(this->scene);
  object->use();
  
  this->children.insert(object);
}

void Object::setScene(Scene *scene) {
  this->scene = scene;
}

Scene *Object::getScene() {
  return this->scene;
}

// draw

void Object::drawData() {
  glm::mat4 *projection_matrix = this->scene->getActiveCamera()->getCamera()->getProjectionMatrix();
  
  switch(this->type) {
   case OBJECT_TYPE_EMPTY:
     return;
   case OBJECT_TYPE_MESH:
     this->data.mesh->draw(&this->world_matrix, projection_matrix);
     break;
   case OBJECT_TYPE_CAMERA:
     this->data.camera->updateMatrix();
     break;
   default:
     log(LOG_LEVEL_WARN, "cannot draw Object of unknown type " + std::to_string((int) this->type) + " (" + this->getName() + ")");
  }
}

void Object::drawChildren() {
  for(Object *child : this->children) {
    child->draw();
  }
}

void Object::draw() {
  if(this->visible == false) {
    return;
  }
  
  this->updateMatrix();

  if(this->visible_self)
    this->drawData();

  if(this->visible_children)
    this->drawChildren();
}
