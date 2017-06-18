
#include "world.hpp"

#include "program.hpp"
#include "scene.hpp"
#include "log.hpp"

extern Program *program;

static double MESH_DATA_CUBE[] = {
  // front
  -0.5, -0.5, -0.5,
  -0.5, +0.5, -0.5,
  +0.5, +0.5, -0.5,
  +0.5, +0.5, -0.5,
  +0.5, -0.5, -0.5,
  -0.5, -0.5, -0.5,

  // back
  +0.5, +0.5, +0.5,
  -0.5, +0.5, +0.5,
  -0.5, -0.5, +0.5,
  -0.5, -0.5, +0.5,
  +0.5, -0.5, +0.5,
  +0.5, +0.5, +0.5,
  
  // left
  -0.5, -0.5, +0.5,
  -0.5, +0.5, +0.5,
  -0.5, -0.5, -0.5,
  -0.5, -0.5, -0.5,
  -0.5, +0.5, +0.5,
  -0.5, +0.5, -0.5,
  
  // right
  +0.5, -0.5, -0.5,
  +0.5, +0.5, +0.5,
  +0.5, -0.5, +0.5,
  +0.5, +0.5, -0.5,
  +0.5, +0.5, +0.5,
  +0.5, -0.5, -0.5,
  
  // top
  -0.5, +0.5, -0.5,
  -0.5, +0.5, +0.5,
  +0.5, +0.5, -0.5,
  +0.5, +0.5, -0.5,
  -0.5, +0.5, +0.5,
  +0.5, +0.5, +0.5,
  
  // bottom
  +0.5, -0.5, -0.5,
  -0.5, -0.5, +0.5,
  -0.5, -0.5, -0.5,
  +0.5, -0.5, +0.5,
  -0.5, -0.5, +0.5,
  +0.5, -0.5, -0.5,
};

WorldTile::WorldTile(World *world, int number) {
  
  this->world = world;
  
  this->object = new Object();
  this->object->setName("world tile " + std::to_string(number));

  int grid_size = 100;
  
  double x = (number % grid_size - grid_size/2) * 1.5;
  double y = (number / grid_size - grid_size/2) * 1.5;

  this->object->setPosition(glm::vec3(x, y, 0));
  
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
  
  this->mesh->setMeshData(MESH_DATA_CUBE, 12);
  
  this->mesh->createBuffer();
  
  for(int i=0; i<10000; i++) {
    this->tiles[i] = new WorldTile(this, i);
  }
  
}
