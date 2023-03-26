#pragma once

#include <core/opengl.h>

namespace en61 {

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void bind();
	void unbind();

	void draw_triangles(size_t count);
	void draw_points(size_t count);

protected:
	GLuint _id;
	GLenum _type;
};

} // namespace en61
