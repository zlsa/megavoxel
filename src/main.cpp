
#include <iostream>
#include <stdlib.h>

#include "pflight_config.hpp"
#include "program.hpp"
#include "tree.hpp"
#include "util.hpp"
#include "log.hpp"

Program *program;

int run(int argc, char *argv[]) {

  program = new Program(argc, argv);

  program->parseArgs();
  program->parseConfig();
  
  program->displayVersion();
  
  program->createWindow();
  
  program->dump();

  while(!program->shouldExit()) {
    program->tick();
  }

  delete program;
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
