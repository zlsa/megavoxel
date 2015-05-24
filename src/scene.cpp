
#include "scene.hpp"

Scene::Scene() {
  this->clear_color = glm::vec4(1.0, 1.0, 0.0, 1.0);
}

glm::vec4 Scene::getClearColor() {
  return(this->clear_color);
}

void Scene::draw() {
  glm::vec4 cc = this->getClearColor();
  
  glClearColor(cc.x, cc.y, cc.z, cc.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  this->root.draw();
}
