#pragma once

#include <core/event/event.h>
#include <core/event/mouse.h>
#include <core/event/key.h>
#include <core/controls.h>
#include <core/window.h>
#include <core/opengl.h>

namespace en61 {

class Camera {
public:
	Camera(Ref<Window> window);

	enum Direction {
		Forward,
		Backward,
		Left,
		Right
	};

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

	void CalcFrameTime();
	void ProcessInput();
	void ProcessKeyboard(Direction direction, float delta);
	void ProcessMouseMovement(float xoffset, float yoffset, bool limit = true);
	void ProcessMouseScroll(float yoffset);

	void OnEvent(Event &event);
	void OnMouseScrolled(MouseScrolledEvent &event);
	void OnMouseMoved(MouseMovedEvent &event);

	void SetPosition(glm::vec3 pos) { _position = pos; }
	glm::vec3 GetPosition() const { return _position; }

protected:
	void updateCameraVectors();

protected:
	Ref<Window> _window;

	float _last_x;
	float _last_y;
	float _ratio;
	float _delta_time = 0.0f;
	float _last_frame = 0.0f;

	glm::vec3 _position;
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _world_up;

	float _yaw = 90.0f;
	float _pitch = 0.0f;

	float _move_speed = 7.f;
	float _mouse_sensivity = 0.1f;
	float _zoom = 45.f;
	float _zoom_speed = 2.f;
};

} // namespace en61
