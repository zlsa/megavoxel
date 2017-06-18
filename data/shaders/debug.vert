#version 150

uniform mat4 u_mvp_matrix;

in vec4 i_position;
out vec4 v_position;
 
void main (void) {
  gl_Position = u_mvp_matrix * i_position;

  v_position = i_position;
}
