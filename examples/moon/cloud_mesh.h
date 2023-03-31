#pragma once

#include <core/renderer/mesh.h>
#include <core/renderer/vertex_array.h>
#include <core/renderer/vertex_buffer.h>

#include "particle.h"
#include "kdtree.h"

using namespace en61;

class CloudMesh: public IMesh {
public:
	CloudMesh(size_t count = 1500);
	~CloudMesh();

	void Draw() override;

protected:
	KDTree *_tree;
	std::vector<Particle*> _particles;
	std::vector<Particle*> _nearParticles;

	VertexBuffer _buffer;
	VertexArray _array;

	float *_positions;
	size_t _count; // of particles
};
