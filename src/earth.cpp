
#include "earth.hpp"

#include "program.hpp"
#include "scene.hpp"
#include "log.hpp"

extern Program *program;

EarthTile::EarthTile(Earth *earth, int number) {
  
  this->earth = earth;
  
  this->object.setName("earth tile " + std::to_string(number));
  
  this->object.setType(OBJECT_TYPE_MESH);
  this->object.setMesh(this->earth->mesh);
  
  this->earth->group.add(&this->object);
}

Earth::Earth() {

}

void Earth::create() {
  Scene *scene = program->getScene();

  Shader *shader = scene->newShader();
  shader->setName("earth shader");
  shader->createShader("debug.vert", "debug.frag");
  
  this->material = scene->newMaterial();

  this->material->setShader(shader);

  this->group.setName("earth group");
  scene->add(&this->group);

  this->mesh = scene->newMesh();

  this->mesh->setMeshData(MESH_DATA_TRIANGLE, 1);
  
  this->mesh->createBuffer();
  
  for(int i=0; i<6; i++) {
    this->tiles[i] = new EarthTile(this, i);
  }
  
}
