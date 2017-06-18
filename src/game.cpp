
#include "game.hpp"

#include <cmath>
#include <chrono>

#include <glm/ext.hpp>
#include <glm/vec3.hpp>
#include "shader.hpp"
#include "log.hpp"

Game::Game() {
  this->scene = new Scene();
  this->scene->create();

  this->camera = new Object();
  this->camera->setType(OBJECT_TYPE_CAMERA);
  this->camera->setCamera(this->scene->newCamera());

  this->scene->setActiveCamera(this->camera);

  this->scene->add(this->camera);

  this->camera->setPosition(glm::vec3(0.0, 0.0, -10.0));

  this->world = new World();
}

Game::~Game() {
  log(LOG_LEVEL_DUMP, "deleting Game");
  
  delete this->scene;
  delete this->world;
}

void Game::create() {
  this->world->create(this->scene);
}

Scene *Game::getScene() {
  return this->scene;
}

void Game::tick() {
  using namespace std::chrono;
  
  double seconds = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() / 1000.0;

  //this->world->group->setPosition(glm::vec3(sin(seconds * 0.5) * 30, cos(seconds * 0.2) * 30, cos(seconds * 0.8) * 30));

  //log(LOG_LEVEL_VERBOSE, glm::to_string(this->world->group->getPosition()));
}

