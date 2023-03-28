#version 430 core

layout(location = 0) in vec4 position;

uniform mat4 model;
uniform mat4 view;

void main() {
	gl_Position = view * model * position;
}
