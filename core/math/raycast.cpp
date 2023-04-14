#include <core/math/raycast.h>

#include <core/controls.h>
#include <glm/geometric.hpp>

namespace en61 {

glm::vec3 Raycast::Create(float xpos, float ypos) {

	// viewport coordinates
	glm::vec2 viewport_coords = glm::vec2(xpos, ypos);

	// normalized coordinates
	glm::vec2 normalized_coords = ToNDS(viewport_coords);

	// homogeneous clip coordinates
	glm::vec4 clip_coords = ToClipCoords(normalized_coords);

	// view space
	glm::vec4 eye_coords = ToEyeCoords(clip_coords);

	// world space
	glm::vec3 world_ray = ToWorldCoords(eye_coords);

	return glm::normalize(world_ray);
}

glm::vec3 Raycast::CreateFromMouse() {
	auto [xpos, ypos] = MousePosition();
	return Create(static_cast<float>(xpos), static_cast<float>(ypos));
}

glm::vec2 Raycast::ToNDS(glm::vec2 viewport_coords) {		 
	float x = (2.0f * viewport_coords.x) / _window->Width() - 1.0f;
	float y = 1.0f - (2.0f * viewport_coords.y) / _window->Height();

	return glm::vec2(x, y);
}

glm::vec4 Raycast::ToClipCoords(glm::vec2 normalized_coords) {
	return glm::vec4(normalized_coords.x, normalized_coords.y, -1.f, 1.f);
}

glm::vec4 Raycast::ToEyeCoords(glm::vec4 clip_coords) {
	glm::mat4 inverted = glm::inverse(_proj);
	glm::vec4 eye_coords = inverted * clip_coords;
	return glm::vec4(clip_coords.x, clip_coords.y, -1.f, 0.f);
}


glm::vec3 Raycast::ToWorldCoords(glm::vec4 eye_coords) {
	glm::mat4 inverted_view = glm::inverse(_view);
	return inverted_view * eye_coords;
}

void Raycast::UpdateData(glm::mat4 view, glm::mat4 proj) {
	_view = view;
	_proj = proj;
}

} // namespace en61
