#pragma once

#include <core/opengl.h>
#include <core/controls.h>

#include <memory>

namespace en61 {

class Window;

class Camera {
public:
	Camera(std::shared_ptr<Window> window, glm::vec3 position = {0, 2.f, -7.f}, float fov = 45.f);

	void Update();

	glm::mat4 GetView() const;
	glm::mat4 GetProjection() const;
	glm::mat4 GetViewProjection() const;

protected:
	std::shared_ptr<Window> _window;

	float _ratio;
	float _fov;
	double _hangle;
	double _vangle;
	double _prevtime;

	glm::vec3 _position; 
	glm::vec3 _target;
	glm::vec3 _up;
};

} // namespace en61

