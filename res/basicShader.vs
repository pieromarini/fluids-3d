#version 400

in vec3 position;
in vec3 normal;

out vec3 normal0;

uniform mat4 model; 
uniform mat4 camera;

void main() {
	gl_Position = camera * model * vec4(position, 1.0);
	normal0 = (model * vec4(normal, 0.0)).xyz;
}
