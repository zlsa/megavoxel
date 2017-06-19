
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
  
  double near;
  double far;

  glm::mat4 projection_matrix;
  
 public:
  Camera();
  //~Camera();

  void setObject(Object *object);
  void setFov(double fov);
  void setLimits(double near, double far);
  
  void updateMatrix();

  glm::mat4 *getProjectionMatrix();
};
