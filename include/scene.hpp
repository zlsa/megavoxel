
#pragma once

class Scene;

#include "object.hpp"

#include "shader.hpp"

#include "material.hpp"

#include "camera.hpp"
#include "mesh.hpp"

class Scene {
 protected:
  glm::vec4 clear_color;
  
  Object *root;
  
  Material *materials;

  // The active camera.
  Object *active_camera;

  long frames_rendered;
  
  long fps_bucket_frames;
  double fps_bucket_time;

  double fps;

 public:
  long draw_calls;
  
  Scene();
  ~Scene();

  void create();
  
  glm::vec4 getClearColor();

  void draw();
  void add(Object *object);

  void updateFramerate();

  void setActiveCamera(Object *camera);
  Object *getActiveCamera();
};

