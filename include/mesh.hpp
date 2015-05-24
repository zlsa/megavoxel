
#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "datablock.hpp"

struct Triangle {
  int vertex[3];
};

enum MeshState {
  MESH_STATE_NOT_READY = 0,
  MESH_STATE_READY
};

class Mesh: public Datablock {
 protected:
  std::vector<glm::vec3> vertices;
  std::vector<Triangle> triangles;
  glm::mat4 world_matrix;
  
  GLuint vertex_array_object;
  GLuint vertex_buffer_object_triangles;
  GLuint vertex_buffer_object_uvs;

  MeshState state;

 public:
  Mesh();

  void setVertices(std::vector<glm::vec3> vertices);
  void setTriangles(std::vector<Triangle> triangles);

  // get/set
  int getVertexNumber();
  
  void createBuffer();

  void draw();
};

#endif
