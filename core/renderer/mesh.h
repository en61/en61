#pragma once

#include <core/renderer/mesh.h>
#include <core/renderer/interfaces.h>
#include <core/renderer/vertex_array.h>
#include <core/renderer/vertex_buffer.h>

#include <string>

namespace en61 {

class Mesh: public MeshInterface {
public:
	Mesh() = default;

	void Load(const std::string &path);
	void Draw();

protected:
	size_t _vnum{0};
	VertexArray _array;

	VertexBuffer _position_buffer;
	VertexBuffer _normal_buffer;
	VertexBuffer _uv_buffer;
	VertexBuffer _tangent_buffer;
};

} // namespace en61
