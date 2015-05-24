
#ifndef SCENE_H
#define SCENE_H

#include "earth.hpp"
#include "object.hpp"

class Scene {
 protected:
  Earth earth;
  glm::vec4 clear_color;
  
  Object root;

 public:
  Scene();

  glm::vec4 getClearColor();

  void draw();
};

#endif
