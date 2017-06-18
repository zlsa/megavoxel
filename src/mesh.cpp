
#include "mesh.hpp"

#include "log.hpp"
#include "megavoxel_config.hpp"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4, glm::ivec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

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
    
#if !MEGAVOXEL_HEADLESS
  if(this->state == MESH_STATE_READY) {
    glDeleteVertexArrays(1, &this->vertex_array_object);
    glDeleteBuffers(2, &this->vertex_buffer_object_triangles);
  }
#endif
  
}

void Mesh::setObject(Object *object) {
  this->object = object;
}

// get/set

void Mesh::setMaterial(Material *material) {
  this->material = material;
};

void Mesh::setMeshData(double *triangles, int triangle_number) {
  this->triangles = triangles;
  
  this->triangle_number = triangle_number;
}

// get vertex number

int Mesh::getVertexNumber() {
  return(this->triangle_number * 3);
}

// OpenGL interface

void Mesh::createBuffer() {
  log(LOG_LEVEL_DUMP, "creating OpenGL buffer");
  
#if !MEGAVOXEL_HEADLESS
  glGenVertexArrays(1, &this->vertex_array_object);
  glBindVertexArray(this->vertex_array_object);

  // triangles

  glGenBuffers(1, &this->vertex_buffer_object_triangles);
  glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer_object_triangles);

  // Three floating-point coordinates per vertex.
  int size = this->getVertexNumber() * 3 * sizeof(GLfloat);
  GLfloat *buf = new GLfloat[this->getVertexNumber() * 3];

  // Copy over the buffer.
  for(unsigned int i=0; i<this->getVertexNumber() * 3; i++) {
    buf[i] = (GLfloat) this->triangles[i];
  }

  glBufferData(GL_ARRAY_BUFFER, size, buf, GL_STATIC_DRAW);

  log(LOG_LEVEL_DUMP, "Sent " + std::to_string(size) +  " bytes of mesh data");
  
  delete[] buf;
#endif
  
  this->state = MESH_STATE_READY;
}

// draw mesh

void Mesh::bind() {
  assert(this->state == MESH_STATE_READY);
  
#if !MEGAVOXEL_HEADLESS
  glBindVertexArray(this->vertex_array_object);
#endif
  
}

void Mesh::draw(const glm::mat4 *matrix, const glm::mat4 *camera_matrix) {
  assert(this->material);
  
  this->material->bind();
  
  Shader *shader = this->material->getShader();
  
#if !MEGAVOXEL_HEADLESS
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(this->vertex_array_object);
  //glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer_object_triangles);

  glUniformMatrix4fv(shader->getUniformLocation("u_mvp_matrix"), 1, GL_FALSE, (const GLfloat *)
                     (glm::value_ptr((*camera_matrix) * (*matrix))));

  glDrawArrays(GL_TRIANGLES, 0, this->getVertexNumber());
#endif
  
}
