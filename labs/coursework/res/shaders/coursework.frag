#version 440

// Point light information
struct point_light {
  vec4 light_colour;
  vec3 position;
  float constant;
  float linear;
  float quadratic;
};

// Material information
struct material {
  vec4 emissive;
  vec4 diffuse_reflection;
  vec4 specular_reflection;
  float shininess;
};

// Point light for the scene
uniform point_light point;
// Material for the object
uniform material mat;
// Eye position
uniform vec3 eye_pos;
// Texture
uniform sampler2D tex;

// Incoming position
layout(location = 0) in vec3 vertex_position;
// Incoming normal
layout(location = 1) in vec3 transformed_normal;
// Incoming texture coordinate
layout(location = 2) in vec2 tex_coord;

// Outgoing colour
layout(location = 0) out vec4 colour;

void main() {
  // Get distance between point light and vertex
  float d = distance(point.position, vertex_position);
  // Calculate attenuation factor
  float af = (point.constant + (point.linear*d) + (point.quadratic*d*d));
  // Calculate light colour
  vec4 light_colour = point.light_colour/af;
  // Calculate light dir
  vec3 light_dir = normalize(point.position - vertex_position);
  // Calculate diffuse component
  float kd = max(dot(transformed_normal, light_dir), 0.0);
  vec4 diffuse = kd * (mat.diffuse_reflection * light_colour);
  // Calculate view direction
  vec3 view_dir = normalize(eye_pos-vertex_position);
  // Calculate half vector
  vec3 half_vector = normalize(light_dir + view_dir);
  // Calculate specular component
  float ks = pow(max(dot(transformed_normal, half_vector), 0.0), mat.shininess);
  vec4 specular = ks * (mat.specular_reflection * light_colour);
  // Sample texture
  vec4 tex_colour = texture(tex, tex_coord);
  // Calculate primary colour component
  vec4 primary = mat.emissive + diffuse;
  // Calculate final colour - remember alpha
  vec4 secondary = specular;
  colour = primary * tex_colour + secondary;
  colour.a = 1.0;
}