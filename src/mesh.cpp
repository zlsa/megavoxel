
#include "mesh.hpp"

#include "log.hpp"

Mesh::Mesh() {
  this->setName("unnamed Mesh");

  this->state = MESH_STATE_NOT_READY;

  this->triangles = NULL;
  this->triangle_number = 0;

  this->vertex_array_object            = 0;
  this->vertex_buffer_object_triangles = 0;
}

void Mesh::deleteSelf() {
  if(this->triangles != NULL)
    delete this->triangles;
    
  if(this->state == MESH_STATE_READY) {
    glDeleteVertexArrays(1, &this->vertex_array_object);
    glDeleteBuffers(2, &this->vertex_buffer_object_triangles);
  }
}

// get/set

void Mesh::setMeshData(double *triangles, int triangle_number) {
  this->triangles = triangles;
  
  this->triangle_number = triangle_number;
}

// OpenGL interface

void Mesh::createBuffer() {
  log(LOG_LEVEL_VERBOSE, "Creating OpenGL buffer");
  
  glGenVertexArrays(1, &this->vertex_array_object);
  glBindVertexArray(this->vertex_array_object);

  log(LOG_LEVEL_VERBOSE, "VAO index: " + std::to_string(this->vertex_array_object));
  
  // triangles

  glGenBuffers(1, &this->vertex_buffer_object_triangles);
  glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer_object_triangles);

  log(LOG_LEVEL_VERBOSE, "VBO index: " + std::to_string(this->vertex_buffer_object_triangles));
  
  // Three floating-point coordinates per vertex.
  int size = this->getVertexNumber() * 3 * sizeof(GLfloat);
  GLfloat *buf = new GLfloat[this->getVertexNumber() * 3];

  // Copy over the buffer.
  for(unsigned int i=0; i<this->getVertexNumber() * 3; i++) {
    buf[i] = (GLfloat) this->triangles[i];
  }

  glBufferData(GL_ARRAY_BUFFER, size, buf, GL_STATIC_DRAW);

  log(LOG_LEVEL_VERBOSE, "Sent mesh data (" + std::to_string(size) +  " bytes)");
  
  delete[] buf;
  
  this->state = MESH_STATE_READY;
}

// get vertex number

int Mesh::getVertexNumber() {
  return(this->triangle_number * 3);
}

// draw mesh

void Mesh::use() {
  assert(this->state == MESH_STATE_READY);
  
  glBindVertexArray(this->vertex_array_object);
}

void Mesh::draw(glm::mat4 matrix) {
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(this->vertex_array_object);
  //glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer_object_triangles);
  
  glDrawArrays(GL_TRIANGLES, 0, this->getVertexNumber());
}
