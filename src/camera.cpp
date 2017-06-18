
#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "program.hpp"

#include "log.hpp"

extern Program *program;

Camera::Camera() {
  this->fov = 80;
}

void Camera::setObject(Object *object) {
  this->object = object;
}

void Camera::updateMatrix() {
  float aspect = 1.0;

#if !MEGAVOXEL_HEADLESS
  int width, height;
  glfwGetFramebufferSize(program->getWindow()->getWindow(), &width, &height);
  aspect = (float) width / height;
#endif
  
  this->projection_matrix = glm::perspective((float) this->fov, aspect, 0.2f, 100.0f) * this->object->getMatrix(true);
}

glm::mat4 *Camera::getProjectionMatrix() {
  return &this->projection_matrix;
}
