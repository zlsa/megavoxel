
#pragma once

class Object;

#include <set>
#include <string>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>

#include "datablock.hpp"

#include "mesh.hpp"
#include "camera.hpp"

enum ObjectType {
  OBJECT_TYPE_EMPTY = 0,
  OBJECT_TYPE_MESH = 1,
  OBJECT_TYPE_CAMERA = 2,
};

class Object: public Datablock {
 protected:

  glm::vec3 position;
  glm::quat orientation;

  glm::mat4 matrix;
  glm::mat4 world_matrix;

  ObjectType type;

  union {
    Mesh *mesh;
    Camera *camera;
  };

  Scene *scene;
  
  Object *parent;
  std::set<Object*> children;

 public:
  Object();

  void deleteSelf();
  void deleteData();

  void setPosition(glm::vec3 pos);
  glm::vec3 getPosition();

  void setOrientation(glm::vec3 rot);
  void setOrientation(glm::quat rot);
  glm::quat getOrientation();

  void setType(ObjectType type);

  void setMesh(Mesh *mesh);
  void setCamera(Camera *camera);

  Camera *getCamera();

  glm::mat4 getMatrix(bool world=false);
  void updateMatrix();

  void setParent(Object *object);
  void remove(Object *object);
  void add(Object *object);
  
  void setScene(Scene *scene);

  void drawData();
  void drawChildren();
  void draw();
};

