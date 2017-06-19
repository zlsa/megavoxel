
#include "world.hpp"

#include "program.hpp"
#include "scene.hpp"
#include "log.hpp"

extern Program *program;

World::World() {
  this->map = new Map();
}

World::~World() {
  
  log(LOG_LEVEL_DUMP, "deleting World");

  delete this->map;
}

void World::create(Scene *scene) {
  
  this->root = new Object();
  this->root->setName("world root");
  scene->add(this->root);

  this->map->create(this, scene);

}
