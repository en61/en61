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

void CloudMesh::Draw() {
	std::fill_n(_positions, _count * 3, -5);
	if (_particles.size() < _count - 6) {
		for (int i = 0; i < 6; i++)
			_particles.push_back(new Particle);
	}

	_tree = new KDTree(2, _particles);

	for (unsigned int i = 0; i < _particles.size(); i++)
	{
		_nearParticles.clear();
		_tree->FindInRange(0.3f,_particles[i]->Position(), _nearParticles);
		_particles[i]->Update(_nearParticles);

		if (_particles[i]->Lifetime() < 0) {
			delete _particles[i];
			_particles.erase(_particles.begin()+i);
			i--;
		}
		else {
			_positions[i * 3]   = _particles[i]->X();
			_positions[i * 3 + 1] = _particles[i]->Y();
			_positions[i * 3 + 2] = _particles[i]->Z();
		}
	}
	delete _tree;

	_array.Bind();
	_buffer.Set(sizeof(float) * _count * 3, _positions);
	_buffer.EnableAttribute(0, 3);
	_array.Unbind();

	_array.DrawPoints(_count);
}
