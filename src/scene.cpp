
#include "scene.hpp"

#include <glm/vec3.hpp>
#include "shader.hpp"
#include "log.hpp"

Scene::Scene() {
  this->root = new Object();
  this->root->use();
  
  this->root->setName("root object");
  this->clear_color = glm::vec4(0.9, 1.0, 1.0, 1.0);
}

Scene::~Scene() {
  log(LOG_LEVEL_DUMP, "deleting Scene");
  this->root->unuse();
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

  this->root->draw();
}

void Scene::add(Object *object) {
  this->root->add(object);
}

Shader *Scene::newShader(std::string vertex_filename, std::string fragment_filename) {
  Shader *shader = new Shader(vertex_filename, fragment_filename);
  
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
