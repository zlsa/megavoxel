
#include "mesh.hpp"

#include <string>

#include "log.hpp"

Datablock::Datablock() {
  log(LOG_LEVEL_DUMP, "creating Datablock");
  this->uses = 0;
}

// Ref-counting

void Datablock::use() {
  this->uses += 1;
  log(LOG_LEVEL_DUMP, "+1 (" + std::to_string(this->uses) + "): '" + this->getName() + "'");
}

void Datablock::unuse() {
  this->uses -= 1;
  log(LOG_LEVEL_DUMP, "-1 (" + std::to_string(this->uses) + "): '" + this->getName() + "'");
  
//  if(this->uses <= 0) this->deleteSelf();
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

