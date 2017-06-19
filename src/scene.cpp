
#include "scene.hpp"

#include <chrono>
#include <glm/vec3.hpp>
#include "shader.hpp"
#include "log.hpp"

Scene::Scene() {
  this->root = new Object();

  this->root->setScene(this);
  
  this->root->setName("root object");
  this->clear_color = glm::vec4(0.0, 0.0, 0.0, 1.0);

  this->active_camera = NULL;

  this->frames_rendered = 0;
  
  this->fps_bucket_frames = 0;
  this->fps_bucket_time = 0;
  
  this->fps = 0;
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

  this->draw_calls = 0;
  
#if !MEGAVOXEL_HEADLESS
  glClearColor(cc.x, cc.y, cc.z, cc.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif

  this->root->draw();
  
  this->frames_rendered += 1;
  this->fps_bucket_frames += 1;
  
  this->updateFramerate();
}

void Scene::add(Object *object) {
  this->root->add(object);
}

void Scene::updateFramerate() {
  using namespace std::chrono;
  
  double now = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() / 1000.0;
  double elapsed = now - this->fps_bucket_time;
  
  if(this->fps_bucket_frames >= 100 || elapsed > 2.0) {
    this->fps = this->fps_bucket_frames / elapsed;

    log(LOG_LEVEL_DUMP, "fps: " + std::to_string(this->fps) + " (last frame had " + std::to_string(this->draw_calls) + " draw calls)");
      
    this->fps_bucket_frames = 0;
    this->fps_bucket_time = now;
  }
}

void Scene::setActiveCamera(Object *camera) {
  assert(camera->getType() == OBJECT_TYPE_CAMERA);
  
  this->active_camera = camera;
}

Object *Scene::getActiveCamera() {
  assert(this->active_camera);
  
  return this->active_camera;
}
