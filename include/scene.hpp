
#pragma once

class Scene;

#include "object.hpp"

#include "shader.hpp"

#include "material.hpp"

#include "camera.hpp"
#include "mesh.hpp"

class Scene {
 protected:
  glm::vec4 clear_color;
  
  Object *root;
  
  Material *materials;

  // The active camera.
  Object *active_camera;

 public:
  Scene();
  ~Scene();

  void create();
  
  glm::vec4 getClearColor();

  void draw();
  void add(Object *object);
  
  Shader *newShader();
  Material *newMaterial();
  Mesh *newMesh();
  Camera *newCamera();

  void setActiveCamera(Object *camera);
  Object *getActiveCamera();
};

