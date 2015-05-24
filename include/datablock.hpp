
#ifndef DATABLOCK_H
#define DATABLOCK_H

class Datablock {
 private:
  int uses;

 public:
  Datablock();

  void use();
  void unuse();
  
};

#endif
