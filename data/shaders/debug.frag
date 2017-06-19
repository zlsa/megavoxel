#version 150
 
uniform mat4 u_model_matrix;
uniform vec3 u_light_position;

uniform vec3 u_light_direction;

in vec3 v_position;
in vec3 v_normal;
in vec2 v_uv;

in vec3 v_world_position;
in vec3 v_world_normal;

out vec4 fragColor;

void main(void) {

  //vec3 light_normal = normalize(u_light_position - v_world_position);

  vec3 light_normal = normalize(u_light_direction);
  
  float light_brightness = max(dot(v_world_normal, light_normal), 0.0);

  //float light_brightness = 1;

  //float light_attenuation = clamp(1.0 - distance(u_light_position, v_world_position) * 0.03, 0.0, 1.0);

  //light_attenuation *= light_attenuation;

  //light_brightness *= light_attenuation;

  vec3 color = vec3(1.0, 1.0, 1.0);

  vec3 light_color = vec3(1.1, 1.0, 0.95);
  vec3 ambient_color = vec3(0.02, 0.055, 0.08);
  
  fragColor = vec4(light_brightness * light_color * color + ambient_color, 1.0);

  //fragColor = vec4(0.01 * , 1.0);
  
  //fragColor = vec4((v_world_normal).xyz, 1.0);
  
  //fragColor = vec4(0.5 + 0.5 * v_position.xyz, 1.0);
  
  //fragColor = vec4(0.5 + 0.5 * v_world_position.xyz, 1.0);
}
