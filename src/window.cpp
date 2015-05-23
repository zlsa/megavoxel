
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
  this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);
  
  if(this->window == NULL) {
    glfwTerminate();
    log(LOG_LEVEL_FATAL, "could not create window (you need OpenGL version > " WINDOW_MINIMUM_VERSION ")");
  }
  
  glfwMakeContextCurrent(this->window);
  
  log(LOG_LEVEL_DUMP, "created " + this->getStringSize() + " window with title '" + this->title + "'");

  osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("test.ac");
  if(!model) {
    log(LOG_LEVEL_FATAL, "could not open model 'test.ac'");
  }

  this->viewer = new osgViewer::Viewer;
  this->graphics_window = this->viewer->setUpViewerAsEmbeddedInWindow(0, 0, this->width, this->height);
  this->viewer->setSceneData(model.get());
  this->viewer->setCameraManipulator(new osgGA::TrackballManipulator);
  this->viewer->addEventHandler(new osgViewer::StatsHandler);
  this->viewer->realize();
}

void Window::tick() {
  glfwGetWindowSize(this->window, &this->width, &this->height);
  
  this->should_close = glfwWindowShouldClose(this->window);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(!this->viewer.valid())
    log(LOG_LEVEL_FATAL, "osg viewer is not valid");
  if(!this->graphics_window.valid())
    log(LOG_LEVEL_FATAL, "osg graphics window is not valid");

  osg::DisplaySettings::instance()->setNumMultiSamples(8);
  
  this->graphics_window->resized(this->graphics_window->getTraits()->x,
                                 this->graphics_window->getTraits()->y,
                                 this->width,
                                 this->height);
  this->graphics_window->getEventQueue()->windowResize(this->graphics_window->getTraits()->x,
                                                       this->graphics_window->getTraits()->y,
                                                       this->width,
                                                       this->height);

  double dx, dy;
  glfwGetCursorPos(this->window, &dx, &dy);
  int x = dx, y = dy;

  this->graphics_window->getEventQueue()->mouseMotion(x, y);
                   
  for(int i=0; i<3; i++) {
    if(glfwGetMouseButton(this->window, i) == GLFW_PRESS) {
      this->graphics_window->getEventQueue()->mouseButtonPress(x, y, i);
    } else {
      this->graphics_window->getEventQueue()->mouseButtonRelease(x, y, i);
    }
  }
  
  this->viewer->frame();

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
