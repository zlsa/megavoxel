
add_executable(pflight
  log.cpp
  util.cpp
  tree.cpp
  config.cpp
  program.cpp
  main.cpp)

target_link_libraries(pflight "${Boost_LIBRARIES}" -lboost_system)

install(TARGETS pflight DESTINATION bin)
