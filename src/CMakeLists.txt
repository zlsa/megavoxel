
add_executable(pflight
  log.cpp
  util.cpp
  tree.cpp
  program.cpp
  main.cpp)
install(TARGETS pflight DESTINATION bin)
