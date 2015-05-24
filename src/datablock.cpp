
#include "mesh.hpp"

#include <string>

#include "log.hpp"

Datablock::Datablock() {
  
#if LOG_SCENEGRAPH_CHANGES
  log(LOG_LEVEL_DUMP, "creating Datablock");
#endif
  this->uses = 0;
}

// Ref-counting

void Datablock::use() {
  this->uses += 1;

#if LOG_REFCOUNT
  log(LOG_LEVEL_DUMP, "+1 (" + std::to_string(this->uses) + "): '" + this->getName() + "'");
#endif
}

void Datablock::unuse() {
  this->uses -= 1;
  
#if LOG_REFCOUNT
  log(LOG_LEVEL_DUMP, "-1 (" + std::to_string(this->uses) + "): '" + this->getName() + "'");
#endif
  
  if(this->uses <= 0) this->deleteSelf();
  
}

void Datablock::deleteSelf() {

}

bool Datablock::isReady() {
  return this->ready;
}

// name
void Datablock::setName(std::string name) {
  this->name = name;
}

std::string Datablock::getName() {
  return(this->name);
}

