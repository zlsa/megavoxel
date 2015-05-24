
#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct Triangle {
  int vertex[3];
};

class Mesh {
 protected:
  int uses;
  std::vector<glm::vec3> vertices;
  std::vector<Triangle> triangles;
  glm::mat4 world_matrix;
  
  GLuint vertex_array_object;
  GLuint vertex_buffer_object_triangles;
  GLuint vertex_buffer_object_uvs;

 public:
  Mesh();

  void use();
  void unuse();
  
  void setVertices(std::vector<glm::vec3> vertices);
  void setTriangles(std::vector<Triangle> triangles);
  
  void createBuffer();
};

#endif
