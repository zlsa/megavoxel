
#include "camera.hpp"

#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "program.hpp"

#include "log.hpp"

extern Program *program;

Camera::Camera() {
#if LOG_SCENEGRAPH_CHANGES
  log(LOG_LEVEL_DUMP, "creating Camera");
#endif
  
  this->setName("unnamed Camera (data)");
  
  this->fov = 80;

  this->near = 0.05;
  this->far = 100000;
}

void Camera::setObject(Object *object) {
  this->object = object;
}

void Camera::setFov(double fov) {
  this->fov = fov;
}

void Camera::setLimits(double near, double far) {
  this->near = near;
  this->far = far;

  if(near > far) {
    this->far = near + 0.001;
  }
}

void Camera::updateMatrix() {
  float aspect = 1.0;

#if !MEGAVOXEL_HEADLESS
  int width, height;
  glfwGetFramebufferSize(program->getWindow()->getWindow(), &width, &height);
  aspect = (float) width / height;
#endif
  
  this->projection_matrix = glm::perspective(glm::radians((float) this->fov), aspect,
                                             (float) this->near, (float) this->far) * this->object->getMatrix(true);
}

glm::mat4 *Camera::getProjectionMatrix() {
  return &this->projection_matrix;
}
