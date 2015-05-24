
#ifndef OBJECT_H
#define OBJECT_H

#include <set>
#include <string>
#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>

#include "mesh.hpp"
#include "camera.hpp"
#include "datablock.hpp"

enum ObjectType {
  OBJECT_TYPE_NONE = 0,
  OBJECT_TYPE_EMPTY,
  OBJECT_TYPE_MESH,
  OBJECT_TYPE_CAMERA,
};

class Object: public Datablock {
 protected:
  
  glm::mat4 matrix;
  glm::mat4 world_matrix;

  ObjectType type;
  
  Mesh *mesh;
  Camera *camera;

  Object *parent;
  std::set<Object*> children;
  
 public:
  Object();
  
  void deleteSelf();
  void deleteData();
  
  glm::vec3 getPosition();
  
  void setType(ObjectType type);
  
  void setMesh(Mesh *mesh);

  glm::mat4 getMatrix(bool world=false);
  void updateMatrix();

  void setParent(Object *object);
  void remove(Object *object);
  void add(Object *object);

  void drawMesh();
  void drawChildren();
  void draw();
};

#endif
