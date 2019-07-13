#version 400

in vec3 position;
in vec3 normal;

out vec3 fragVert;
out vec3 fragNormal;

uniform mat4 model;
uniform mat4 camera; 

void main() {
	fragVert = position;
	fragNormal = normal;
	gl_Position = camera * model * vec4(position, 1.0);
}
