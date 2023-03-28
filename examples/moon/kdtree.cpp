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

		float start = particles.front()->position()[axis];
		float middle = particles[median]->position()[axis];
		float end = particles.back()->position()[axis];


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
void KDTree::find_in_range(float squared_range, glm::vec3 position, std::vector<Particle*> &near_particles, float largest_distance) {

	float distance = std::pow(glm::length(position - _point->position()), 2);

	if (distance < largest_distance) {
		//if the distance is within the range, add this node's particle to the vector
		if (distance <= squared_range)
			near_particles.push_back(_point);
		else
			largest_distance = distance;

		//if there are nodes beneath the one being checked, call the function in those nodes
		if (_left)
			_left->find_in_range(squared_range, position, near_particles, largest_distance);
		if (_right)
			_right->find_in_range(squared_range, position, near_particles, largest_distance);
	}
}
