
#ifndef EARTH_H
#define EARTH_H

#include <array>
#include "object.hpp"

class Earth;

class EarthTile {
 protected:
  Earth *earth;
  Object object;
  
 public:
  EarthTile(Earth *earth);
};

class Earth {
 protected:
  std::array<EarthTile*, 6> tiles;

 public:
  Mesh *mesh;
  
  Earth();
};

#endif
