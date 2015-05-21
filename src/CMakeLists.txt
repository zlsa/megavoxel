
add_executable(pflight
  log.cpp
  util.cpp
  tree.cpp
  main.cpp)
install(TARGETS pflight DESTINATION bin)
