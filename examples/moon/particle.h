#pragma once

#include <core/opengl.h>
#include <vector>

class Particle {
public:
	Particle();

	void Update(std::vector<Particle*> &near_particles);

	glm::vec3 Position() const { return _position; }
	glm::vec3 Velocity() const { return _velocity; }

	int Lifetime() const { return _lifetime; }

	float X() const { return _position.x; }
	float Y() const { return _position.y; }
	float Z() const { return _position.z; }

protected:
	glm::vec3 _position;
	glm::vec3 _velocity;
	int _lifetime;
};
