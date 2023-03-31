#include "particle.h"

#include <core/random.h>

using namespace en61;

Particle::Particle() {
	_lifetime = 250;
	_velocity = glm::vec3(0,0,0);
	_position = glm::vec3((RandomFloat() - 0.5) / 3, -0.5, (RandomFloat() - 0.5) / 3);
}

void Particle::Update(std::vector<Particle*> &near_particles) {

	static constexpr float delta = 7.0f / 1000.0f;

	glm::vec3 acceleration(0.0f);
	acceleration.y += 0.6f;
	_lifetime--;

	for (size_t i = 0; i < near_particles.size(); i++) {
		if (near_particles[i] != this) {
		    glm::vec3 increase = _position - near_particles[i]->_position;
		    increase *= near_particles.size() > 20 ? 0.02f : -2.0f;
		    acceleration += increase;
		}
	}

	_velocity += acceleration * delta;
	_position += _velocity * delta;
}
