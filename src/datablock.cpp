
#include "mesh.hpp"

#include <string>

#include "log.hpp"

long datablock_number = 0;

std::set<Datablock*> datablocks;

Datablock::Datablock() {

  this->setName("unnamed Datablock");
  
#if LOG_SCENEGRAPH_CHANGES
  log(LOG_LEVEL_DUMP, "creating Datablock");
#endif
  this->uses = 0;

  datablock_number += 1;
  
  datablocks.insert(this);
}

Datablock::~Datablock() {
}

size_t Datablock::operator() (const Datablock &datablock) const {
  return (size_t) (&datablock);
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
  
  if(this->uses <= 0 && !this->untouchable) {
#if LOG_DATABLOCK_REMOVE
    log(LOG_LEVEL_DUMP, "no more users; removing '" + this->getName() + "'");
#endif
    
    datablock_number -= 1;
    datablocks.erase(this);
    
    log(LOG_LEVEL_DUMP, "deleting '" + this->getName() + "'");
    delete this;

    //this->deleteSelf();
  }
  
}

bool Datablock::isReady() {
  return this->ready;
}

// name
void Datablock::setName(std::string name) {
  log(LOG_LEVEL_VERBOSE, "renaming '" + this->getName() + "' to '" + name + "'");
  this->name = name;
}

std::string Datablock::getName() {
  return(this->name);
}

