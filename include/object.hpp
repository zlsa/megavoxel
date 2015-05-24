
#ifndef OBJECT_H
#define OBJECT_H

#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>

#include "mesh.hpp"

enum ObjectType {
  OBJECT_TYPE_NONE = 0,
  OBJECT_TYPE_EMPTY,
  OBJECT_TYPE_MESH,
};

class Object {
 protected:
  glm::mat4 matrix;
  glm::mat4 world_matrix;

  Mesh *mesh;

 public:
  Object();
  glm::vec3 getPosition();
  
  void setMesh(Mesh *mesh);
};

#endif
