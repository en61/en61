#pragma once

#include <core/opengl.h>

#include <vector>

namespace en61 {

class VertexBuffer {
public:
	VertexBuffer(GLenum type = GL_ARRAY_BUFFER);
	~VertexBuffer();

	void bind();
	void unbind();

	void set(GLsizeiptr size, const GLvoid *data, GLenum usage = GL_STATIC_DRAW);
	
	template <class _type>
	void set(const std::vector<_type> &data, size_t size = 1, GLenum usage = GL_STATIC_DRAW) {
		set(data.size() * sizeof(_type) * size, &data[0], usage);
	}

	void enable_attribute(GLuint index, GLint size, GLenum type = GL_FLOAT, GLboolean normalized = GL_FALSE, GLsizei stride = 0, const GLvoid *data = 0);
	void disable_attribute(GLuint index);

protected:
	GLuint _id;
	GLenum _type;
};

} // namespace en61
