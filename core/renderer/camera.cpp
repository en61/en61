#include <core/controls.h>
#include <core/renderer/camera.h>

#include <core/common.h>
#include <core/window.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/trigonometric.hpp>

namespace en61 {

Camera::Camera(Ref<Window> window)
	: _window(window) {
	
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

glm::mat4 Camera::GetProjection() const {
	static constexpr float znear = 0.1f;
	static constexpr float zfar = 100.f;

	return glm::perspective(glm::radians(_fov), _ratio, znear, zfar);
}

glm::mat4 Camera::GetViewProjection() const {
	return GetProjection() * GetView();
}

void Camera::Update() {
	double current_time = glfwGetTime();
	float frame_time = current_time - _prevtime;

	double width = _window->Width();
	double height = _window->Height();

	auto [xpos, ypos] = MousePosition();
	SetMousePosition(width / 2, height / 2);

	_hangle += _camera_speed * float(width / 2 - xpos);
	_vangle += _camera_speed * float(height / 2 - ypos);

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
	

	if (IsKeyPressed(GLFW_KEY_UP) || IsKeyPressed(GLFW_KEY_W)) {
		_position += direction * frame_time * _move_speed;
	}

	// Move backward
	if (IsKeyPressed(GLFW_KEY_DOWN) || IsKeyPressed(GLFW_KEY_S)) {
		_position -= direction * frame_time * _move_speed;
	}

	// Strafe right
	if (IsKeyPressed(GLFW_KEY_RIGHT) || IsKeyPressed(GLFW_KEY_D)) {
		_position += right * frame_time * _move_speed;
	}

	// Strafe left
	if (IsKeyPressed(GLFW_KEY_LEFT) || IsKeyPressed(GLFW_KEY_A)) {
		_position -= right * frame_time * _move_speed;
	}

	_target = _position + direction;
	_up = glm::cross(right, direction);

	_prevtime = current_time;
}

void Camera::SetMoveSpeed(float speed) {
	_move_speed = speed;
}

void Camera::SetCameraSpeed(float speed) {
	_camera_speed = speed;
}

void Camera::SetFieldOfView(float fov) {
	_fov = fov;
}

void Camera::SetPosition(const glm::vec3 &position) {
	_position = position;
}

} // namespace en61
