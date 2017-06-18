
#pragma once

class Camera;

#include <glm/glm.hpp>

#include "scene.hpp"

#include "datablock.hpp"
#include "object.hpp"

class Camera: public Datablock {
 protected:
  Object *object;
  
  double fov;

  glm::mat4 projection_matrix;
  
 public:
  Camera();

  void setObject(Object *object);
  
  void updateMatrix();

  glm::mat4 *getProjectionMatrix();
};
