
#pragma once

#include <string>

class Datablock {
 private:
  int uses;
  bool ready;

 protected:
  std::string name;
  bool untouchable = false;

 public:
  Datablock();
  virtual ~Datablock();

  void use();
  void unuse();

  bool isReady();

  void setName(std::string name);
  std::string getName();
    
  size_t operator() (const Datablock &datablock) const;
  
};

