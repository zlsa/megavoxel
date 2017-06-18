
#include "world.hpp"

#include "program.hpp"
#include "scene.hpp"
#include "log.hpp"

extern Program *program;

WorldTile::WorldTile(World *world, int number) {
  
  this->world = world;
  
  this->object = new Object();
  this->object->setName("world tile " + std::to_string(number));
  
  this->object->setType(OBJECT_TYPE_MESH);
  this->object->setMesh(this->world->mesh);

  this->world->group->add(this->object);
}

World::World() {

}

void World::create(Scene *scene) {
  
  Shader *shader = scene->newShader();
  shader->setName("world shader");
  shader->createShader("debug.vert", "debug.frag");
  
  this->material = scene->newMaterial();

  this->material->setShader(shader);

  this->group = new Object();
  this->group->setName("world group");
  scene->add(this->group);

  this->mesh = scene->newMesh();

  this->mesh->setMaterial(this->material);
  
  this->mesh->setMeshData(MESH_DATA_SQUARE, 2);
  
  this->mesh->createBuffer();
  
  for(int i=0; i<6; i++) {
    this->tiles[i] = new WorldTile(this, i);
  }
  
}
