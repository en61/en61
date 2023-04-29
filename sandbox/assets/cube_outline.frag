#version 430 core

in vec2 texCoord;

uniform sampler2D colorTexture;

out vec4 color;

void main() {
	vec3 tex = vec3(texture(colorTexture, texCoord));
    tex.x = mod(tex.x + 5, 256);
	color = vec4(tex, 1);
}
