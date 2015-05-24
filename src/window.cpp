
#include "window.hpp"

#include "log.hpp"
#include "util.hpp"
#include "program.hpp"

extern Program *program;

Window::Window() {
  this->window = NULL;
  this->title  = "pFlight";
  this->width  = 1;
  this->height = 1;
  this->fullscreen = false;

  this->should_close = false;
}

void Window::setSize(int width, int height) {
  this->width = clamp(1, width);
  this->height = clamp(1, height);
}

std::string Window::getStringSize() {
  return(std::to_string(this->width) + "x" + std::to_string(this->height));
}

void Window::create() {

  int samples = program->getConfig()->getIntValue("render_aa_samples", 0);
  log(LOG_LEVEL_DUMP, "aa samples: " + std::to_string(samples));
  glfwWindowHint(GLFW_SAMPLES, samples);
  
  this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);
  
  if(this->window == NULL) {
    glfwTerminate();
    log(LOG_LEVEL_FATAL, "could not create window (you need OpenGL version > " WINDOW_MINIMUM_VERSION ")");
  }
  
  glfwMakeContextCurrent(this->window);

  GLenum err = glewInit();
  if(err != GLEW_OK) {
    log(LOG_LEVEL_FATAL, "could not initialize GLEW");
  }
  
  log(LOG_LEVEL_DUMP, "created " + this->getStringSize() + " window with title '" + this->title + "'");
}

void Window::update_size() {
  glfwGetWindowSize(this->window, &this->width, &this->height);
}

bool Window::shouldClose() {
  return(this->should_close);
}

void Window::tick() {
  this->should_close = glfwWindowShouldClose(this->window);

  this->update_size();

  this->draw();

  glfwSwapBuffers(this->window);
  glfwPollEvents();
}

void Window::draw() {
  Scene *scene = program->getScene();

  scene->draw();
}

// DESTRUCTOR

Window::~Window() {
  log(LOG_LEVEL_DUMP, "deleting Window");
}
