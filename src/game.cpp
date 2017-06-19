
#include "game.hpp"

#include <glm/ext.hpp>
#include <glm/vec3.hpp>
#include "shader.hpp"
#include "log.hpp"

#include "util.hpp"

Game::Game() {
  this->scene = new Scene();
  this->scene->create();

  this->camera = new Object();
  this->camera->setType(OBJECT_TYPE_CAMERA);
  this->camera->setCamera(new Camera());

  this->camera->setName("main camera");
  
  this->camera->getCamera()->setFov(5);
  this->camera->getCamera()->setLimits(100, 800);

  this->scene->setActiveCamera(this->camera);

  this->scene->add(this->camera);

  this->camera->setPosition(glm::vec3(0.0, -500.0, 100.0));
  this->camera->setOrientation(glm::vec3(glm::radians(101.0), 0.0, 0.0));

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
  this->world->root->setOrientation(glm::vec3(0, 0.0, fmod(getTimeSinceEpoch() * 0.5, 360)));
}

