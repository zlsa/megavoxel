
#include "path.hpp"
#include "log.hpp"

const char* home = getenv("HOME");

Path::Path() {
  log(LOG_LEVEL_NOTICE, "foobar");
}

Path::Path(std::string path) {
  
}
