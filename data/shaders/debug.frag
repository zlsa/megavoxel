#version 150
 
in vec4 v_position;
out vec4 fragColor;
 
void main(void) {
  fragColor = vec4((0.5 + (0.5 * v_position)).xyz, 0.5);
}
