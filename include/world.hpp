
#ifndef WORLD_H
#define WORLD_H

#include <array>
#include "object.hpp"

#include "scene.hpp"

class World;

class WorldTile {
 protected:
  World *world;
  Object *object;
  
 public:
  WorldTile(World *world, int number);
};

class World {
 protected:
  std::array<WorldTile*, 10000> tiles;

 public:
  Mesh *mesh;
  Object *group;
  Material *material;
  
  World();
  
  void create(Scene *scene);
};

#endif
