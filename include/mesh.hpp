
#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "datablock.hpp"
#include "material.hpp"

static double MESH_DATA_TRIANGLE[] = {
  -1.0, -1.0, 0.5,
  +0.0, +1.0, 0.5,
  +1.0, -1.0, 0.5,
};

enum MeshState {
  MESH_STATE_NOT_READY = 0,
  MESH_STATE_READY = 0,
};

class Mesh: public Datablock {
 protected:
  MeshState state;
  
  double *triangles;
  int triangle_number;

  Material *material;
  
  GLuint vertex_array_object;
  GLuint vertex_buffer_object_triangles;

 public:
  Mesh();
  
  void deleteSelf();

  void setMeshData(double *triangles, int triangle_number);

  // get/set
  int getVertexNumber();
  
  void createBuffer();

  void use();
  void draw(glm::mat4 matrix);
};

#endif
