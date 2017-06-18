
#ifndef GAME_H
#define GAME_H

#include "scene.hpp"
#include "world.hpp"

class Game {
 protected:
  Scene *scene;
  World *world;
  
  Object *camera;
  
 public:
  Game();
  ~Game();

  void create();

  Scene *getScene();

  void tick();
};

#endif
