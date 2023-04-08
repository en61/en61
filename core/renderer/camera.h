#pragma once

#include <core/opengl.h>
#include <core/controls.h>
#include <core/common.h>

namespace en61 {

class Window;

class Camera {
public:
	Camera(Ref<Window> window);

	void Update();

	glm::mat4 GetView() const;
	glm::mat4 GetProjection() const;
	glm::mat4 GetViewProjection() const;
	
	void SetMoveSpeed(float speed);
	void SetCameraSpeed(float speed);
	void SetFieldOfView(float fov);
	void SetPosition(const glm::vec3 &position);

protected:
	Ref<Window> _window;

	float _ratio;
	double _hangle;
	double _vangle;
	double _prevtime;

	float _fov = 45.f;
	float _move_speed = 10.f;
	float _camera_speed = 0.001f;

	glm::vec3 _position = {0, 2, -7}; 
	glm::vec3 _target;
	glm::vec3 _up;
};

} // namespace en61
