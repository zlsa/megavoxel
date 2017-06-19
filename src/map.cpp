
#include <cstdlib>
#include "map.hpp"

#include "program.hpp"
#include "scene.hpp"
#include "log.hpp"

extern Program *program;

TileCoordinates::TileCoordinates(double x, double y) {
  this->x = x;
  this->y = y;
  this->z = 0;
}

TileCoordinates::TileCoordinates(double x, double y, double z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

std::string TileCoordinates::to_string() {
  return "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ", " + std::to_string(this->z) + ")";
}

MapOctant::MapOctant(MapTile *map_tile, MapOctant *parent, OctantCorner corner) {

  this->init(map_tile);

  this->parent = parent;
  this->level = this->parent->level + 1;

  // Set up this octant within the parent.
  this->corner = corner;
  this->size = this->parent->size * 0.5;

  double x, y, z;

  x = (corner >> 0) & 1;
  y = (corner >> 1) & 1;
  z = (corner >> 2) & 1;

  double s = 1;
  double hs = 0.5;

  this->offset = glm::vec3(x * s - hs, y * s - hs, z * s - hs);
  
  this->object->setName("map octant " + std::to_string(this->level) + ": " + std::to_string(corner));

  this->object->setPosition(this->offset);
  this->object->setScale(0.5);

  this->parent->object->add(this->object);
  
  if(rand() % 100 < 40) {
    this->object->visible_self = false;

    return;
  }
  
  if(this->level < this->map->octant_maximum_subdivisions) {
    if(rand() % 100 < 80) {
      this->subdivide();
    }
  }
  
}

MapOctant::MapOctant(MapTile *map_tile, TileCoordinates *location) {
  this->init(map_tile);

  this->level = 0;

  this->size = this->map->octant_largest_size;
  this->corner = OCTANT_CORNER_LARGEST;
  
  this->object->setPosition(glm::vec3(location->x, location->y, location->z));
  this->object->setScale(this->size);
  
  this->map_tile->root->add(this->object);
  
  this->object->setName("map octant " + location->to_string());
  
  this->subdivide();
}

void MapOctant::init(MapTile *map_tile) {
  
  this->parent = NULL;
  this->location = NULL;

  this->map_tile = map_tile;

  this->map = map_tile->map;
  
  this->object = new Object();
  this->object->setName("map octant");
  
  this->object->use();
  
  this->subdivided = false;
  
  this->object->setType(OBJECT_TYPE_MESH);
  this->object->setMesh(this->map->mesh);
}

MapOctant::~MapOctant() {

  this->object->unuse();
  
  //log(LOG_LEVEL_DUMP, "deleting MapOctant " + this->object->getName());

  if(this->isSubdivided()) {
    
    for(int i=0; i<8; i++) {
      delete this->children[i];
    }
    
  }

  delete this->location;
  
}

bool MapOctant::isSubdivided() {
  return this->subdivided;
}
  
void MapOctant::subdivide() {
  
  //log(LOG_LEVEL_DUMP, "subdividing '" + this->object->getName() + "'");
  
  this->subdivided = true;

  this->object->visible_self = false;

  for(int i=0; i<8; i++) {
    this->children[i] = new MapOctant(this->map_tile, this, i);
  }
  
}

MapTile::MapTile(Map *map, TileCoordinates *location) {
  this->map = map;

  this->location = location;

  this->root = new Object();
  this->root->setName("map tile " + location->to_string());
  
  this->root->use();
  
  this->map->root->add(this->root);

  for(int i=0; i<1; i++) {
    this->octants.push_back(new MapOctant(this, new TileCoordinates(location->x, location->y, -i * map->octant_largest_size)));
  }
  
}

MapTile::~MapTile() {
  
  //log(LOG_LEVEL_DUMP, "deleting MapTile " + this->root->getName());
  
  this->root->unuse();

  for(int i=0; i<this->octants.size(); i++) {
    delete this->octants[i];
  }
    
  delete this->location;
}

Map::Map() {
  this->octant_largest_size = 32;
  this->octant_maximum_subdivisions = 5;
}

Map::~Map() {
  log(LOG_LEVEL_DUMP, "deleting Map " + this->root->getName());
  
  this->root->unuse();

  for(int i=0; i<this->tiles.size(); i++) {
    delete this->tiles[i];
  }

}

void Map::create(World *world, Scene *scene) {

  // Create shader.
  Shader *shader = new Shader();
  shader->setName("map shader");
  shader->createShader("debug.vert", "debug.frag");

  // Create material.
  this->material = new Material();
  this->material->setName("map material");
  this->material->setShader(shader);

  // Create root object group.
  this->root = new Object();
  this->root->setName("map root");
  this->root->use();
  
  world->root->add(this->root);

  // Create mesh.
  this->mesh = new Mesh();
  this->mesh->setName("cube mesh");
  
  this->mesh->setMaterial(this->material);
  this->mesh->setMeshData(MESH_DATA_CUBE, 12);
  this->mesh->createBuffer();

  int size = 1;

  double octant_size = this->octant_largest_size;
  
  for(int x=-size/2; x<=size/2; x++) {
    for(int y=-size/2; y<=size/2; y++) {
      this->tiles.push_back(new MapTile(this, new TileCoordinates((float) x, (float) y)));
    }
  }
}
