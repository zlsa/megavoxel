
#include "mesh.hpp"

#include "log.hpp"
#include "megavoxel_config.hpp"

#include "util.hpp"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4, glm::ivec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtc/matrix_inverse.hpp>

Mesh::Mesh() {
#if LOG_SCENEGRAPH_CHANGES
  log(LOG_LEVEL_DUMP, "creating Mesh");
#endif
  
  this->setName("unnamed Mesh");

  this->state = MESH_STATE_NOT_READY;

  this->triangles = NULL;
  this->triangle_number = 0;

  this->material = NULL;

  this->vertex_array_object            = 0;
  this->vertex_buffer_object_triangles = 0;
}

Mesh::~Mesh() {
  
  if(this->triangles != NULL)
    delete this->triangles;

  if(this->material)
    this->material->unuse();
    
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
  if(this->material != NULL) {
    this->material->unuse();
  }

  this->material = material;
  material->use();
};

void Mesh::setMeshData(double *triangles, int triangle_number) {

  this->triangle_number = triangle_number;
  
  this->triangles = new double[this->getArraySize()];

  for(unsigned int i=0; i<this->getArraySize(); i++) {
    this->triangles[i] = triangles[i];
  }
  
}

// get vertex number

int Mesh::getVertexNumber() {
  return this->triangle_number * 3;
}

int Mesh::getArraySize() {
  // Position, normal, and UV coordinates.
  return this->getVertexNumber() * 8;
}

// OpenGL interface

void Mesh::createBuffer() {
  log(LOG_LEVEL_DUMP, "creating OpenGL buffer");
  
#if !MEGAVOXEL_HEADLESS
  glGenVertexArrays(1, &this->vertex_array_object);
  glBindVertexArray(this->vertex_array_object);

  // To store the position of each vertex.

  glGenBuffers(1, &this->vertex_buffer_object_triangles);
  glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer_object_triangles);

  // Size of the buffer, in bytes.
  int buf_size = this->getArraySize() * sizeof(GLfloat);
  GLfloat *buf = new GLfloat[this->getArraySize()];

  // Copy over the buffer.
  for(unsigned int i=0; i<this->getArraySize(); i++) {
    buf[i] = (GLfloat) this->triangles[i];
  }

  glBufferData(GL_ARRAY_BUFFER, buf_size, buf, GL_STATIC_DRAW);

  Shader *shader = this->material->getShader();

  int a_position = shader->getAttributeLocation("a_position");
  int a_normal = shader->getAttributeLocation("a_normal");
  int a_uv = shader->getAttributeLocation("a_uv");
  
  glVertexAttribPointer(a_position, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, BUFFER_OFFSET(0, GLfloat));
  glVertexAttribPointer(a_normal, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, BUFFER_OFFSET(3, GLfloat));
  glVertexAttribPointer(a_uv, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, BUFFER_OFFSET(5, GLfloat));
  
  glEnableVertexAttribArray(a_position);
  glEnableVertexAttribArray(a_normal);
  glEnableVertexAttribArray(a_uv);
  
  log(LOG_LEVEL_DUMP, "Sent " + std::to_string(buf_size) +  " bytes of mesh data");
  
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
  this->bind();

  glUniformMatrix4fv(shader->getUniformLocation("u_model_matrix"), 1, GL_FALSE,
                     (const GLfloat *) (glm::value_ptr(*matrix)));

  //glUniform3f(shader->getUniformLocation("u_light_position"), -10.0, 0.0, sin(getTimeSinceEpoch() * 2.0) * 10.0);
  glUniform3f(shader->getUniformLocation("u_light_direction"), -10.0, -5.0, -15.0);

  glUniformMatrix3fv(shader->getUniformLocation("u_normal_matrix"), 1, GL_FALSE,
                     (const GLfloat *) (glm::value_ptr(glm::inverseTranspose(glm::mat3(*matrix)))));

  glUniformMatrix4fv(shader->getUniformLocation("u_view_matrix"), 1, GL_FALSE,
                     (const GLfloat *) (glm::value_ptr((*camera_matrix) * (*matrix))));

  glDrawArrays(GL_TRIANGLES, 0, this->getVertexNumber());
#endif
  
  this->object->getScene()->draw_calls += 1;
  
}
