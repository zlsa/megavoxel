
#include "window.hpp"

#include "log.hpp"
#include "util.hpp"
#include "program.hpp"

extern Program *program;

Window::Window() {
  this->window = NULL;
  this->title  = "MegaVoxel";
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
#if !MEGAVOXEL_HEADLESS
  int samples = program->getConfig()->getIntValue("render_aa_samples", 0);
  
  log(LOG_LEVEL_DUMP, "aa samples: " + std::to_string(samples));
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, WINDOW_MINIMUM_VERSION_MAJOR);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, WINDOW_MINIMUM_VERSION_MINOR);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  glfwWindowHint(GLFW_SAMPLES, samples);
  
  this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);
  
  if(this->window == NULL) {
    glfwTerminate();
    log(LOG_LEVEL_FATAL, "could not create window (you need OpenGL version > " WINDOW_MINIMUM_VERSION ")");
  }
  
  glfwMakeContextCurrent(this->window);

  glewExperimental = GL_TRUE;
  
  GLenum err = glewInit();
  if(err != GLEW_OK) {
    log(LOG_LEVEL_FATAL, "could not initialize GLEW");
  }

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  
  // Enable depth test.
  glEnable(GL_DEPTH_TEST);

  // Disable vsync.
  glfwSwapInterval(0);

  //glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  log(LOG_LEVEL_DUMP, "created " + this->getStringSize() + " window with title '" + this->title + "'");
#else
  log(LOG_LEVEL_WARN, "running headless; not creating window");
#endif
}

GLFWwindow *Window::getWindow() {
  return this->window;
}

void Window::update_size() {
#if !MEGAVOXEL_HEADLESS
  glfwGetWindowSize(this->window, &this->width, &this->height);
#endif
}

bool Window::shouldClose() {
  return this->should_close;
}

void Window::tick() {
#if !MEGAVOXEL_HEADLESS
  this->should_close = glfwWindowShouldClose(this->window);
#endif

  this->update_size();

  if(program->getGame()) {
    this->drawScene(program->getGame()->getScene());
  }

#if !MEGAVOXEL_HEADLESS
  glfwSwapBuffers(this->window);
  glfwPollEvents();
#endif
}

void Window::drawScene(Scene *scene) {
  
#if !MEGAVOXEL_HEADLESS
  int width, height;
  glfwGetFramebufferSize(this->window, &width, &height);
  glViewport(0, 0, width, height);
#endif
  
  scene->draw();
  
}

// DESTRUCTOR

Window::~Window() {
  log(LOG_LEVEL_DUMP, "deleting Window");
}
