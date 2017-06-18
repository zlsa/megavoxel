#version 150

uniform mat4 u_mvp_matrix;

in vec4 position;
 
void main (void) {
  gl_Position = u_mvp_matrix * position;
}
