
#pragma once

class Mesh;

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "scene.hpp"

#include "datablock.hpp"
#include "object.hpp"
#include "material.hpp"

static double MESH_DATA_TRIANGLE[] = {
  -1.0, -1.0, 0,
  +0.0, +1.0, 0,
  +1.0, -1.0, 0,
};

static double MESH_DATA_SQUARE[] = {
  -1.0, -1.0, 0,
  -1.0, +1.0, 0,
  +1.0, +1.0, 0,
  +1.0, +1.0, 0,
  +1.0, -1.0, 0,
  -1.0, -1.0, 0,
};

static double MESH_DATA_CUBE[] = {
  // front
  -0.5, -0.5, -0.5,
  +0.0, +0.0, -1.0,
  +0.0, +0.0,
  
  -0.5, +0.5, -0.5,
  +0.0, +0.0, -1.0,
  +0.0, +0.0,

  +0.5, +0.5, -0.5,
  +0.0, +0.0, -1.0,
  +0.0, +0.0,

  +0.5, +0.5, -0.5,
  +0.0, +0.0, -1.0,
  +0.0, +0.0,

  +0.5, -0.5, -0.5,
  +0.0, +0.0, -1.0,
  +0.0, +0.0,

  -0.5, -0.5, -0.5,
  +0.0, +0.0, -1.0,
  +0.0, +0.0,

  // back
  +0.5, +0.5, +0.5,
  +0.0, +0.0, +1.0,
  +0.0, +0.0,

  -0.5, +0.5, +0.5,
  +0.0, +0.0, +1.0,
  +0.0, +0.0,

  -0.5, -0.5, +0.5,
  +0.0, +0.0, +1.0,
  +0.0, +0.0,

  -0.5, -0.5, +0.5,
  +0.0, +0.0, +1.0,
  +0.0, +0.0,

  +0.5, -0.5, +0.5,
  +0.0, +0.0, +1.0,
  +0.0, +0.0,

  +0.5, +0.5, +0.5,
  +0.0, +0.0, +1.0,
  +0.0, +0.0,

  // left
  -0.5, -0.5, +0.5,
  -1.0, +0.0, +0.0,
  +0.0, +0.0,

  -0.5, +0.5, +0.5,
  -1.0, +0.0, +0.0,
  +0.0, +0.0,

  -0.5, -0.5, -0.5,
  -1.0, +0.0, +0.0,
  +0.0, +0.0,

  -0.5, -0.5, -0.5,
  -1.0, +0.0, +0.0,
  +0.0, +0.0,

  -0.5, +0.5, +0.5,
  -1.0, +0.0, +0.0,
  +0.0, +0.0,

  -0.5, +0.5, -0.5,
  -1.0, +0.0, +0.0,
  +0.0, +0.0,
  
  // right
  +0.5, -0.5, -0.5,
  +1.0, +0.0, +0.0,
  +0.0, +0.0,

  +0.5, +0.5, +0.5,
  +1.0, +0.0, +0.0,
  +0.0, +0.0,

  +0.5, -0.5, +0.5,
  +1.0, +0.0, +0.0,
  +0.0, +0.0,

  +0.5, +0.5, -0.5,
  +1.0, +0.0, +0.0,
  +0.0, +0.0,

  +0.5, +0.5, +0.5,
  +1.0, +0.0, +0.0,
  +0.0, +0.0,

  +0.5, -0.5, -0.5,
  +1.0, +0.0, +0.0,
  +0.0, +0.0,
  
  // top
  -0.5, +0.5, -0.5,
  +0.0, +1.0, +0.0,
  +0.0, +0.0,

  -0.5, +0.5, +0.5,
  +0.0, +1.0, +0.0,
  +0.0, +0.0,

  +0.5, +0.5, -0.5,
  +0.0, +1.0, +0.0,
  +0.0, +0.0,

  +0.5, +0.5, -0.5,
  +0.0, +1.0, +0.0,
  +0.0, +0.0,

  -0.5, +0.5, +0.5,
  +0.0, +1.0, +0.0,
  +0.0, +0.0,

  +0.5, +0.5, +0.5,
  +0.0, +1.0, +0.0,
  +0.0, +0.0,

  // bottom
  +0.5, -0.5, -0.5,
  +0.0, -1.0, +0.0,
  +0.0, +0.0,

  -0.5, -0.5, +0.5,
  +0.0, -1.0, +0.0,
  +0.0, +0.0,

  -0.5, -0.5, -0.5,
  +0.0, -1.0, +0.0,
  +0.0, +0.0,

  +0.5, -0.5, +0.5,
  +0.0, -1.0, +0.0,
  +0.0, +0.0,

  -0.5, -0.5, +0.5,
  +0.0, -1.0, +0.0,
  +0.0, +0.0,

  +0.5, -0.5, -0.5,
  +0.0, -1.0, +0.0,
  +0.0, +0.0,

};

#define BUFFER_OFFSET(idx, type) ((void*) (idx * sizeof(type)))

enum MeshState {
  MESH_STATE_NOT_READY = 0,
  MESH_STATE_READY = 0,
};

class Mesh: public Datablock {
 protected:
  Object *object;
  
  MeshState state;
  
  double *triangles;
  int triangle_number;

  Material *material;
  
  GLuint vertex_array_object;
  GLuint vertex_buffer_object_triangles;
  GLuint vertex_buffer_object_normals;
  GLuint vertex_buffer_object_uvs;

 public:
  Mesh();
  ~Mesh();
  
  //void deleteSelf();

  void setObject(Object *object);
  
  void setMaterial(Material *material);
  void setMeshData(double *triangles, int triangle_number);

  // get/set
  int getVertexNumber();
  int getArraySize();
  
  void createBuffer();

  void bind();
  void draw(const glm::mat4 *matrix, const glm::mat4 *camera_matrix);
};

