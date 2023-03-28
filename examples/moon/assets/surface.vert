#version 430 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texpos;
layout(location = 3) in vec3 tangent;

uniform mat4 view;
uniform mat4 projection;

out vec2 texCoord;

void main() {
    gl_Position = projection * view * position;
	texCoord = texpos;
}
