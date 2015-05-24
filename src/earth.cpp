
#include "earth.hpp"

#include "scene.hpp"
#include "program.hpp"

extern Program *program;

EarthTile::EarthTile(Earth *earth, int number) {
  
  this->earth = earth;
  
  this->object.setName("earth tile" + std::to_string(number));
  this->object.setMesh(this->earth->mesh);

  this->earth->group.add(&this->object);
}

Earth::Earth() {

}

void Earth::create() {
  Scene *scene = program->getScene();

  this->group.setName("earth group");
  scene->add(&this->group);
  
  for(int i=0; i<6; i++) {
    this->tiles[i] = new EarthTile(this, i);
  }
  
}
