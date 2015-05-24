
#include "mesh.hpp"

Datablock::Datablock() {
  this->uses = 0;

  this->use();
}

// Ref-counting

void Datablock::use() {
  this->uses += 1;
}

void Datablock::unuse() {
  this->uses -= 1;
  if(this->uses == 0) delete this;
}

