#version 430 core

in vec2 texCoord;

uniform sampler2D colorTexture;
uniform vec3 cubeColor;

out vec4 color;

void main() {
	vec3 texColor = vec3(texture(colorTexture, texCoord));
	vec3 combined;
	combined.x = cubeColor.x + texColor.x * 0.2;
	combined.y = cubeColor.y + texColor.y * 0.2;
	combined.z = cubeColor.z + texColor.z * 0.2;
	color = vec4(combined, 1.0f);
}
