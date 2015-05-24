
#ifndef DATABLOCK_H
#define DATABLOCK_H

#include <string>

class Datablock {
 private:
  int uses;
  bool ready;

 protected:
  std::string name;

 public:
  Datablock();

  void deleteSelf();
  
  void use();
  void unuse();

  bool isReady();

  void setName(std::string name);
  std::string getName();
    
};

#endif
