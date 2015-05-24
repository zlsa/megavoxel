
#include "scene.hpp"

Scene::Scene() {
  this->root.setName("root object");
  this->clear_color = glm::vec4(1.0, 1.0, 0.0, 1.0);
}

glm::vec4 Scene::getClearColor() {
  return(this->clear_color);
}

void Scene::create() {
  this->earth.create();
}

void Scene::draw() {
  glm::vec4 cc = this->getClearColor();
  
  glClearColor(cc.x, cc.y, cc.z, cc.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  this->root.draw();
}

void Scene::add(Object *object) {
  this->root.add(object);
}
