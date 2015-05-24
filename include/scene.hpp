
#ifndef SCENE_H
#define SCENE_H

#include "earth.hpp"
#include "object.hpp"

class Scene {
 protected:
  Earth earth;
  glm::vec4 clear_color;
  
  Object *root;
  
  Shader *shaders;
  Material *materials;

 public:
  Scene();
  ~Scene();

  void create();
  
  glm::vec4 getClearColor();

  void draw();
  void add(Object *object);
  
  Shader *newShader(std::string vertex_filename, std::string fragment_filename);
  Material *newMaterial();
  Mesh *newMesh();
};

#endif
