#pragma once

#include <core/renderer/mesh.h>
#include <core/renderer/vertex_array.h>
#include <core/renderer/vertex_buffer.h>

#include <string>


namespace en61 {

class IMesh {
public:
	virtual void Draw() = 0;
};

class Mesh: public IMesh {
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
