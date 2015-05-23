
#include "window.hpp"

#include "log.hpp"
#include "util.hpp"

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
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, WINDOW_MINIMUM_VERSION_MAJOR);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, WINDOW_MINIMUM_VERSION_MINOR);
  
  this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);
  
  if(this->window == NULL) {
    glfwTerminate();
    log(LOG_LEVEL_FATAL, "could not create window (you need OpenGL version > " WINDOW_MINIMUM_VERSION ")");
  }
  
  glfwMakeContextCurrent(this->window);
  
  log(LOG_LEVEL_DUMP, "created " + this->getStringSize() + " window with title '" + this->title + "'");
  
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

}

void Window::tick() {
  this->should_close = glfwWindowShouldClose(this->window);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glfwSwapBuffers(this->window);
  glfwPollEvents();
}

bool Window::shouldClose() {
  return(this->should_close);
}

// DESTRUCTOR

Window::~Window() {
  log(LOG_LEVEL_DUMP, "deleting Window");
}
