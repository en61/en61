#include "kdtree.h"
#include <glm/geometric.hpp>

#include <cmath>
#include <iostream>

KDTree::KDTree(int depth, std::vector<Particle*> particles)
	: _depth(depth) {

	int median = particles.size() / 2;
	_point = particles[median];

	if (particles.size() >= 3) {

		int axis = depth % 3;

		float start = particles.front()->Position()[axis];
		float middle = particles[median]->Position()[axis];
		float end = particles.back()->Position()[axis];


		if (start > end && middle > start || start > middle)
		    std::swap(particles.front(), particles[median]);

		if (start > end && end > middle || middle > end)
		    std::swap(particles.back(), particles[median]);
	}

	std::vector<Particle*> left_cloud, right_cloud;

	for (int i = 0; i < median; i++)
		left_cloud.push_back(particles[i]);

	for (int i = median+1; i < particles.size(); i++)
		right_cloud.push_back(particles[i]);

	if (right_cloud.size() > 0)
		_right = new KDTree(depth + 1, right_cloud);

	if (left_cloud.size() > 0)
		_left = new KDTree(depth + 1, left_cloud);
}

KDTree::~KDTree() {
	if(_right) delete _right;
	if(_left) delete _left;
}

//recursive function to find all the particles within a range of a particle
void KDTree::FindInRange(float squaredRange, glm::vec3 position, std::vector<Particle*> &nearParticles, float largestDistance) {

	float distance = std::pow(glm::length(position - _point->Position()), 2);

	if (distance < largestDistance) {
		//if the distance is within the range, add this node's particle to the vector
		if (distance <= squaredRange)
			nearParticles.push_back(_point);
		else
			largestDistance = distance;

		//if there are nodes beneath the one being checked, call the function in those nodes
		if (_left)
			_left->FindInRange(squaredRange, position, nearParticles, largestDistance);
		if (_right)
			_right->FindInRange(squaredRange, position, nearParticles, largestDistance);
	}
}
