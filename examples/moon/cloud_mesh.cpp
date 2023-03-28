#include "cloud_mesh.h"

CloudMesh::CloudMesh(size_t count): _count(count) {
	_positions = new float[3 * _count];
	_particles.push_back(new Particle);
}

CloudMesh::~CloudMesh() {
	for (auto particle: _particles)
		delete particle;

	delete [] _positions;
}

void CloudMesh::draw() {
	std::fill_n(_positions, _count * 3, -5);
	if (_particles.size() < _count - 6) {
		for (int i = 0; i < 6; i++)
			_particles.push_back(new Particle);
	}

	_tree = new KDTree(2, _particles);

	for (unsigned int i = 0; i < _particles.size(); i++)
	{
		_near_particles.clear();
		_tree->find_in_range(0.3f,_particles[i]->position(), _near_particles);
		_particles[i]->update(_near_particles);

		if (_particles[i]->lifetime() < 0) {
			delete _particles[i];
			_particles.erase(_particles.begin()+i);
			i--;
		}
		else {
			_positions[i * 3]   = _particles[i]->x();
			_positions[i * 3 + 1] = _particles[i]->y();
			_positions[i * 3 + 2] = _particles[i]->z();
		}
	}
	delete _tree;

	_array.bind();
	_buffer.set(sizeof(float) * _count * 3, _positions);
	_buffer.enable_attribute(0, 3);
	_array.unbind();

	_array.draw_points(_count);
}
