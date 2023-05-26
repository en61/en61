#version 430 core

in vec2 texCoord;

uniform sampler2D colorTexture;

out vec4 color;

void main() {
	vec3 texColor = vec3(texture(colorTexture, texCoord));
	color = vec4(texColor, 1.0f);
}

