
#include "megavoxel_config.hpp"

#include <iostream>
#include <stdlib.h>

#include "log.hpp"
#include "program.hpp"
#include "util.hpp"

Program *program;
extern long datablock_number;
extern std::set<Datablock*> datablocks;

void run(int argc, char *argv[]) {

  program = new Program(argc, argv);

  program->parseArgs();
  program->parseConfig();
  
  program->displayVersion();
  
  program->createWindow();
  program->createGame();
  
  program->dump();

  while(!program->shouldExit()) {
    program->tick();
  }

  log(LOG_LEVEL_INFO, "exiting normally");
  
  delete program;

  if(datablock_number > 0) {
    if(datablock_number == 1) {
      log(LOG_LEVEL_WARN, std::to_string(datablock_number) + " datablock not freed");
    } else {
      log(LOG_LEVEL_WARN, std::to_string(datablock_number) + " datablocks not freed");
    }

    for(Datablock *datablock : datablocks) {
      log(LOG_LEVEL_WARN, "not freed: " + datablock->getName());
    }
  } else {
    log(LOG_LEVEL_DEBUG, "all datablocks freed properly");
  }
}

int main(int argc, char *argv[]) {
  try {

    run(argc, argv);
    
    return(EXIT_SUCCESS);
    
  } catch(exit_exception e) {
    if(program) delete program;
    return(EXIT_SUCCESS);
    
  } catch(fatal_exception e) {
    if(program) delete program;
    return(EXIT_FAILURE);
  }
  
}
