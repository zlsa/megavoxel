
#include "mesh.hpp"

#include "log.hpp"


Mesh::Mesh() {
  this->setName("unnamed Mesh");
  
  this->vertex_array_object            = -1;
  this->vertex_buffer_object_triangles = -1;
}

void Mesh::deleteSelf() {
  if(this->vertex_array_object >= 0)
    glDeleteVertexArrays(1, &this->vertex_array_object);
  
  if(this->vertex_buffer_object_triangles >= 0)
    glDeleteBuffers(2, &this->vertex_buffer_object_triangles);
}

// get/set

void Mesh::setVertices(std::vector<glm::vec3> vertices) {
  this->vertices = vertices;
}

void Mesh::setTriangles(std::vector<Triangle> triangles) {
  this->triangles = triangles;
}

// OpenGL interface

void Mesh::createBuffer() {
  glGenVertexArrays(1, &this->vertex_array_object);
  glBindVertexArray(this->vertex_array_object);

  // triangles
  
  glGenBuffers(1, &this->vertex_buffer_object_triangles);
  glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer_object_triangles);

  int size = this->triangles.size() * 3 * 3 * sizeof(GLfloat);
  GLfloat *buf = new GLfloat[size];

  Triangle *triangle;
  glm::vec3 *vertex;
  for(unsigned int i=0; i<this->triangles.size(); i++) {
    triangle = &this->triangles[i];
    for(int j=0; j<3; j++) {
      vertex = &this->vertices[triangle->vertex[j]];
      buf[(i * 3 * 3) + (j * 3) + 0] = vertex->x;
      buf[(i * 3 * 3) + (j * 3) + 1] = vertex->y;
      buf[(i * 3 * 3) + (j * 3) + 2] = vertex->z;
    }
  }
  
  glBufferData(GL_ARRAY_BUFFER, size, buf, GL_STATIC_DRAW);

  delete[] buf;
}

// get vertex number

int Mesh::getVertexNumber() {
  return(this->triangles.size() * 3);
}
  
// draw mesh

void Mesh::draw(glm::mat4 matrix) {
  glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer_object_triangles);
  glDrawArrays(GL_LINE_LOOP, 0, this->getVertexNumber());
}
