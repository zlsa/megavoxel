
#include <iostream>
#include <stdlib.h>

#include "pflight_config.hpp"
#include "util.hpp"
#include "log.hpp"

int run(int argc, char *argv[]) {
  log(LOG_LEVEL_INFO, "pFlight version " + (std::string) PFLIGHT_VERSION);
}

int main(int argc, char *argv[]) {
  try {

    run(argc, argv);
    
    return(EXIT_SUCCESS);
  } catch(exit_exception e) {
    return(EXIT_SUCCESS);
  } catch(fatal_exception e) {
    return(EXIT_FAILURE);
  }
}
