
#include "earth.hpp"

EarthTile::EarthTile(Earth *earth) {
  this->earth = earth;
  
  this->object.setMesh(this->earth->mesh);
}

Earth::Earth() {
  for(int i=0; i<6; i++) {
    this->tiles[i] = new EarthTile(this);
  }
}
