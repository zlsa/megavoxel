
#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "datablock.hpp"
#include "material.hpp"

struct Triangle {
  int vertex[3];
};

class Mesh: public Datablock {
 protected:
  std::vector<glm::vec3> vertices;
  std::vector<Triangle> triangles;
  glm::mat4 world_matrix;

  Material *material;
  
  GLuint vertex_array_object;
  GLuint vertex_buffer_object_triangles;

 public:
  Mesh();
  
  void deleteSelf();

  void setVertices(std::vector<glm::vec3> vertices);
  void setTriangles(std::vector<Triangle> triangles);

  // get/set
  int getVertexNumber();
  
  void createBuffer();

  void draw();
};

#endif
