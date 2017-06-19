
#pragma once

#include <array>
#include "object.hpp"

#include "scene.hpp"
#include "map.hpp"

class World;

class World {
 protected:
  Map *map;

 public:
  Object *root;
  
  World();
  ~World();
  
  void create(Scene *scene);
};
