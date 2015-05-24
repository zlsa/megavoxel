
add_executable(pflight
  log.cpp
  util.cpp
  tree.cpp
  config.cpp
  window.cpp
  mesh.cpp
  object.cpp
  earth.cpp
  program.cpp
  main.cpp)

target_link_libraries(pflight "${Boost_LIBRARIES}" -lboost_system -lGL)
target_link_libraries(pflight ${GLFW_LIBRARIES})
target_link_libraries(pflight ${GLEW_LIBRARIES})

install(TARGETS pflight DESTINATION bin)
