
// A `Map` contains the data representing a single map. It's divided
// into a 2D grid of `MapTile`s, which are divided into a vertical
// stack of `MapOctants`. Each `MapOctant`, when subdivided, contains
// 8 more `MapOctant`. It's `MapOctant`s all the way down.

#pragma once

#include <array>

#include "object.hpp"
#include "scene.hpp"

#include "map.hpp"

class World;

class Map;
class MapTile;
class MapOctant;

typedef short OctantCorner;

#define OCTANT_CORNER_0 (0)
#define OCTANT_CORNER_1 (1)
#define OCTANT_CORNER_2 (2)
#define OCTANT_CORNER_3 (3)
#define OCTANT_CORNER_4 (4)
#define OCTANT_CORNER_5 (5)
#define OCTANT_CORNER_6 (6)
#define OCTANT_CORNER_7 (7)

#define OCTANT_CORNER_LARGEST (8)

class TileCoordinates {
 public:
  double x;
  double y;
  double z;

  TileCoordinates(double x, double y);
  TileCoordinates(double x, double y, double z);

  std::string to_string();
};

//

class MapOctant {
 protected:
  MapTile *map_tile;

  Object *object;

  // If `corner` is `OCTANT_CORNER_LARGEST`, then `parent` *must* be `NULL`
  // and `location` *must* be non-`NULL`. Otherwise, the `NULL`s must
  // be inverted.
  MapOctant *parent;
  TileCoordinates *location;

  // 0 means `corner` is `OCTANT_CORNER_LARGEST`.
  int level;

  // Size of the octant
  double size;

  // Which corner this `MapOctant` is in, within its parent.
  OctantCorner corner;

  bool subdivided;

  // Our offset, relative to the parent.
  glm::vec3 offset;

  MapOctant *children[8];

  void init(MapTile *map);

 public:
  Map *map;
  
  MapOctant(MapTile *map, MapOctant *parent, OctantCorner corner);
  MapOctant(MapTile *map, TileCoordinates *location);
  
  ~MapOctant();
  
  bool isSubdivided();
  void subdivide();
};

// A `MapTile` is a tall vertical stack of `MapOctant`s.

class MapTile {
 protected:
  TileCoordinates *location;
  
  std::vector<MapOctant*> octants;

 public:
  Map *map;
  Object *root;
  
  MapTile(Map *map, TileCoordinates *location);
  
  ~MapTile();
};

class Map {
 protected:
  World *world;
  std::vector<MapTile*> tiles;

 public:
  int octant_largest_size;
  int octant_maximum_subdivisions = 2;
  
  Object *root;
  Mesh *mesh;
  Material *material;
  
  Map();
  
  ~Map();
  
  void create(World *world, Scene *scene);
};
