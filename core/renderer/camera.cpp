#include "core/controls.h"
#include <core/renderer/camera.h>

#include <core/common.h>
#include <core/window.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/trigonometric.hpp>

namespace en61 {

Camera::Camera(std::shared_ptr<Window> window, glm::vec3 position, float fov)
	: _window(window), _position(position), _fov(fov) {
		_ratio = _window->Ratio();
		_prevtime = glfwGetTime();
		_hangle = 0.f;
		_vangle = 0.f;

		window->scroll_callbacks += [this](double xoffset, double yoffset) {
			float new_fov = this->_fov - yoffset * 5;
			if (new_fov > 0 && new_fov < 180)
				this->_fov = new_fov;
		};

	}

glm::mat4 Camera::GetView() const {
	return glm::lookAt(_position, _target, _up);
}

glm::mat4 Camera::GetModel() const {
	return glm::mat4(1.0f);
}

glm::mat4 Camera::GetProjection() const {
	static constexpr float znear = 0.1f;
	static constexpr float zfar = 100.f;

	return glm::perspective(glm::radians(_fov), _ratio, znear, zfar);
}

glm::mat4 Camera::GetMVP() const {
	return GetProjection() * GetView() * GetModel();
}

void Camera::Update() {
	double current_time = glfwGetTime();
	float frame_time = current_time - _prevtime;
	float speed = 0.001f;

	double width = _window->Width();
	double height = _window->Height();

	auto [xpos, ypos] = MousePosition();
	SetMousePosition(width / 2, height / 2);

	_hangle += speed * float(width / 2 - xpos);
	_vangle += speed * float(height / 2 - ypos);

	// direction: spherical coordinates to cartesian coordinates conversion
	glm::vec3 direction = {
		cos(_vangle) * sin(_hangle), 
		sin(_vangle),
		cos(_vangle) * cos(_hangle)
	};

	// right vector
	glm::vec3 right = {
		sin(_hangle - constants::Pi / 2.f),
		0,
		cos(_hangle - constants::Pi / 2.f)
	};
	
	if (IsKeyPressed(GLFW_KEY_UP)) {
		_position += direction * frame_time * speed;
	}
	// Move backward
	if (IsKeyPressed(GLFW_KEY_DOWN)) {
		_position -= direction * frame_time * speed;
	}
	// Strafe right
	if (IsKeyPressed(GLFW_KEY_RIGHT)) {
		_position += right * frame_time * speed;
	}
	// Strafe left
	if (IsKeyPressed(GLFW_KEY_LEFT)) {
		_position -= right * frame_time * speed;
	}

	_target = _position + direction;
	_up = glm::cross(right, direction);
	_prevtime = current_time;
}

} // namespace en61
