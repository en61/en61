#pragma once

#include <core/opengl.h>
#include <core/window.h>

namespace en61 {

struct Ray {
	glm::vec3 origin;
	glm::vec3 direction;
};

class Raycast {
public:
	Raycast(Ref<Window> w)
		: _window(w) { }

	Ray Create(glm::vec3 origin, float xpos, float ypos);
	glm::vec3 GetDirection(float xpos, float ypos);

	glm::vec2 ToNDS(glm::vec2 viewport_coords);
	glm::vec4 ToClipCoords(glm::vec2 normalized_coords);
	glm::vec4 ToEyeCoords(glm::vec4 clip_coords);
	glm::vec3 ToWorldCoords(glm::vec4 eye_coords);

	void UpdateData(glm::mat4 view, glm::mat4 proj);

protected:
	Ref<Window> _window;
	glm::mat4 _view;
	glm::mat4 _proj;
};

} // namespace en61
