#pragma once

#include <core/opengl.h>

namespace en61 {

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void Bind();
	void Unbind();

	void DrawTriangles(size_t count);
	void DrawPoints(size_t count);

protected:
	GLuint _id;
	GLenum _type;
};

} // namespace en61
