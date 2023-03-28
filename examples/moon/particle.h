#pragma once

#include <core/opengl.h>
#include <vector>

class Particle {
public:
	Particle();

	void update(std::vector<Particle*> &near_particles);

	glm::vec3 position() const { return _position; }
	glm::vec3 velocity() const { return _velocity; }

	int lifetime() const { return _lifetime; }

	float x() const { return _position.x; }
	float y() const { return _position.y; }
	float z() const { return _position.z; }

protected:
	glm::vec3 _position;
	glm::vec3 _velocity;
	int _lifetime;
};
