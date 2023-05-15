#include <core/renderer/camera.h>

namespace en61 {

void Camera::OnEvent(Event &event) {
	EventDispatcher d(event);
	d.Handle<MouseScrolledEvent>(BIND_EVENT_FN(OnMouseScrolled));
	d.Handle<MouseMovedEvent>(BIND_EVENT_FN(OnMouseMoved));
}

Camera::Camera(Ref<Window> window)
	: _window(window) {

	_ratio = _window->Ratio();

	_last_x = _window->Width() / 2.0f;
	_last_y = _window->Height() / 2.0f;

	_position = glm::vec3(2, 4, -7);
	_front = glm::vec3(0.0f, 0.0f, -1.0f);
	_up = glm::vec3(0.0f, 1.0f, 0.0f);
	_world_up = _up;

	updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(_position, _position + _front, _up);
}

void Camera::CalcFrameTime() {
	float current = static_cast<float>(glfwGetTime());
	_delta_time = current - _last_frame;
	_last_frame = current;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool limit) {
	xoffset *= _mouse_sensivity;
	yoffset *= _mouse_sensivity;

	_yaw += xoffset;
	_pitch += yoffset;

	if (limit) {
		if (_pitch > 89.0f)
			_pitch = 89.0f;
		if (_pitch < -89.0f)
			_pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
	_zoom -= (float)yoffset * _zoom_speed;
	if (_zoom < 1.0f)
		_zoom = 1.0f;
	if (_zoom > 45.0f)
		_zoom = 45.0f;
}

void Camera::ProcessKeyboard(Direction direction, float delta) {
	float velocity = _move_speed * delta;

	if (direction == Direction::Forward)
		_position += _front * velocity;

	if (direction == Direction::Backward)
		_position -= _front * velocity;

	if (direction == Direction::Left)
		_position -= _right * velocity;

	if (direction == Direction::Right)
		_position += _right * velocity;
}


void Camera::updateCameraVectors() {

	glm::vec3 front;
	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(glm::radians(_pitch));
	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_front = glm::normalize(front);

	_right = glm::normalize(glm::cross(_front, _world_up));
	_up = glm::normalize(glm::cross(_right, _front));
}

glm::mat4 Camera::GetProjectionMatrix() {
	static constexpr float znear = 0.1f;
	static constexpr float zfar = 100.f;

	return glm::perspective(glm::radians(_zoom), _ratio, znear, zfar);
}


void Camera::ProcessInput() {
	
	if (IsKeyPressed(GLFW_KEY_ESCAPE))
		_window->Close();

	if (IsKeyPressed(GLFW_KEY_W))
		ProcessKeyboard(Forward, _delta_time);

	if (IsKeyPressed(GLFW_KEY_S))
		ProcessKeyboard(Backward, _delta_time);

	if (IsKeyPressed(GLFW_KEY_A))
		ProcessKeyboard(Left, _delta_time);

	if (IsKeyPressed(GLFW_KEY_D))
		ProcessKeyboard(Right, _delta_time);
}

void Camera::OnMouseScrolled(MouseScrolledEvent &event) {
	if (std::abs(event.GetYOffset()) > 10) {
		// skip wrong events
		return;
	}

	ProcessMouseScroll(static_cast<float>(event.GetYOffset()));
}

void Camera::OnMouseMoved(MouseMovedEvent &event) {

	float xpos = static_cast<float>(event.GetX());
	float ypos = static_cast<float>(event.GetY());

	float xoffset = xpos - _last_x;
	float yoffset = _last_y - ypos;

	_last_x = xpos;
	_last_y = ypos;

	ProcessMouseMovement(xoffset, yoffset);
}

} // namespace en61
