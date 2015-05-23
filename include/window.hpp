
#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GLFW/glfw3.h>

#define WINDOW_DEFAULT_WIDTH (1024)
#define WINDOW_DEFAULT_HEIGHT (768)

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
  void tick();
  bool shouldClose();
};

#endif
