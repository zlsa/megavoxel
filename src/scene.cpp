
#include "scene.hpp"

#include <glm/vec3.hpp>
#include "shader.hpp"
#include "log.hpp"

Scene::Scene() {
  this->root = new Object();
  this->root->use();

  this->root->setScene(this);
  
  this->root->setName("root object");
  this->clear_color = glm::vec4(0.0, 0.0, 0.0, 1.0);

  this->active_camera = NULL;
}

Scene::~Scene() {
  log(LOG_LEVEL_DUMP, "deleting Scene");
  this->root->unuse();
}

glm::vec4 Scene::getClearColor() {
  return(this->clear_color);
}

void Scene::create() {

}

void Scene::draw() {
  glm::vec4 cc = this->getClearColor();
  
#if !MEGAVOXEL_HEADLESS
  glClearColor(cc.x, cc.y, cc.z, cc.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif

  this->root->draw();
}

void Scene::add(Object *object) {
  this->root->add(object);
}

Shader *Scene::newShader() {
  Shader *shader = new Shader();
  
  return shader;
}

Material *Scene::newMaterial() {
  Material *material = new Material();
  return material;
}

Mesh *Scene::newMesh() {
  Mesh *mesh = new Mesh();
  return mesh;
}

Camera *Scene::newCamera() {
  Camera *camera = new Camera();
  return camera;
}

void Scene::setActiveCamera(Object *camera) {
  assert(camera->getType() == OBJECT_TYPE_CAMERA);
  this->active_camera = camera;
}

Object *Scene::getActiveCamera() {
  assert(this->active_camera);
  
  return this->active_camera;
}
