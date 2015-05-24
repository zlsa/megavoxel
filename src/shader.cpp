
#include "shader.hpp"

Shader::Shader() {
  this->create();
}

Shader::Shader(std::string vertex_filename, std::string fragment_filename) {
  this->create();
  this->loadVertexShader(vertex_filename);
}

void Shader::create() {
  osg::StateSet* brickState = tankNode->getOrCreateStateSet();
  this->program = new osg::Program;
  this->vertex_shader = new osg::Shader(osg::Shader::VERTEX);
  this->fragment_shader = new osg::Shader(osg::Shader::FRAGMENT);

  this->program->addShader(this->vertex_shader);
  this->program->addShader(this->fragment_shader);
}
