#version 150
 
in vec4 v_position;
out vec4 fragColor;
 
void main(void) {
  fragColor = 0.5 + (0.5 * v_position);
}
