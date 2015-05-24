
#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

 public:
  Window();
  ~Window();

  void setSize(int width, int height);
  std::string getStringSize();
  
  void create();
  
  void update_size();
  void tick();
  bool shouldClose();
};

#endif
