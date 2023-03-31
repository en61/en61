#pragma once

#include <core/opengl.h>
#include <vector>
#include "particle.h"

class KDTree {
public:
	KDTree(int depth, std::vector<Particle*> particles);
	~KDTree();

	void FindInRange(float range, glm::vec3 position, std::vector<Particle*> &nearParticles, float largest_distance = 100000.0f);

protected:
	int _depth;
	Particle *_point;
	KDTree *_left{nullptr};
	KDTree *_right{nullptr};
};
