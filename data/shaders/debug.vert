#version 150

uniform mat4 u_model_matrix;
uniform mat3 u_normal_matrix;
uniform mat4 u_view_matrix;

in vec3 a_position;
in vec3 a_normal;
in vec2 a_uv;

out vec3 v_position;
out vec3 v_normal;
out vec2 v_uv;
 
out vec3 v_world_position;
out vec3 v_world_normal;

void main (void) {
  gl_Position = u_view_matrix * vec4(a_position, 1.0);

  v_position = a_position;
  v_normal = a_normal;
  v_uv = a_uv;
  
  v_world_position = (u_model_matrix * vec4(a_position, 1.0)).xyz;
  v_world_normal = normalize(u_normal_matrix * a_normal);
}
