
add_executable(megavoxel-client
  log.cpp
  util.cpp

  config.cpp

  window.cpp

  shader.cpp

  datablock.cpp
  material.cpp
  object.cpp
  mesh.cpp
  camera.cpp

  scene.cpp
  earth.cpp

  program.cpp

  main.cpp)

target_link_libraries(megavoxel-client "${Boost_LIBRARIES}" -lboost_system -lGL)
target_link_libraries(megavoxel-client ${GLFW_LIBRARIES})
target_link_libraries(megavoxel-client ${GLEW_LIBRARIES})

install(TARGETS megavoxel-client DESTINATION bin)
