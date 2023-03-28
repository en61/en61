#version 430 core

in vec2 texCoord;
in vec4 eyePosition;

out vec4 color;

uniform sampler2D colorTexture;
uniform mat4 view;
uniform mat4 projection;

void main() { 
	vec4 worldCenter = vec4(-0.3, 0.5, -2.7, 1);
	vec4 eyeCenter = view * worldCenter;

	vec3 direction = eyeCenter.xyz - eyePosition.xyz;
	float distance = pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2);

	color = texture(colorTexture, texCoord);

	color.b /= clamp(distance * 2, 0, 1);
	color.g /= clamp(distance * 2, 0, 1);
}
