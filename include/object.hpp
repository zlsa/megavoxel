
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
  glm::vec3 scale;
  glm::quat orientation;

  glm::mat4 matrix;
  glm::mat4 world_matrix;

  ObjectType type;

  union {
    Mesh *mesh;
    Camera *camera;
  } data;

  Scene *scene;
  
  Object *parent;
  std::set<Object*> children;

 public:
  bool visible;
  bool visible_self;
  bool visible_children;
  
  Object();
  ~Object();

  //void deleteSelf();
  void deleteData();

  void setPosition(glm::vec3 position);
  glm::vec3 getPosition();

  void setScale(glm::vec3 scale);
  void setScale(double scale);
  glm::vec3 getScale();

  void setOrientation(glm::vec3 orientation);
  void setOrientation(glm::quat orientation);
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
  Scene *getScene();

  void drawData();
  void drawChildren();
  void draw();
};

