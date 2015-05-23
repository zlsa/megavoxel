
#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GLFW/glfw3.h>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>

#define WINDOW_DEFAULT_WIDTH (1024)
#define WINDOW_DEFAULT_HEIGHT (768)

#define WINDOW_MINIMUM_VERSION_MAJOR 3
#define WINDOW_MINIMUM_VERSION_MINOR 2
#define WINDOW_MINIMUM_VERSION       "3.2"

class Window {
 protected:
  GLFWwindow* window;

  std::string title;
  int width;
  int height;
  bool fullscreen;

  bool should_close;

  osg::ref_ptr<osgViewer::Viewer> viewer;
  osg::observer_ptr<osgViewer::GraphicsWindow> graphics_window;

 public:
  Window();
  ~Window();

  void setSize(int width, int height);
  std::string getStringSize();
  void create();
  void tick();
  bool shouldClose();
};

#endif
