#pragma once

#include <core/opengl.h>
#include <core/common.h>

namespace en61 {

struct Ray {
	glm::vec3 origin;
	glm::vec3 direction;
};

class Raycast {
public:
	Raycast(double width, double height);

	Ray CreateFromScreenCentre(glm::vec3 origin);
	Ray Create(glm::vec3 origin, float xpos, float ypos);
	glm::vec3 GetDirection(float xpos, float ypos);

	glm::vec2 ToNDS(glm::vec2 viewport_coords);
	glm::vec4 ToClipCoords(glm::vec2 normalized_coords);
	glm::vec4 ToEyeCoords(glm::vec4 clip_coords);
	glm::vec3 ToWorldCoords(glm::vec4 eye_coords);

	void UpdateMatrices(glm::mat4 view, glm::mat4 proj);
	void UpdateWindowSize(double width, double height);

protected:
	glm::mat4 _view;
	glm::mat4 _proj;
	double _width;
	double _height;
};

} // namespace en61
