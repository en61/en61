#pragma once

#include <core/opengl.h>

#include <vector>

namespace en61 {

class VertexBuffer {
public:
	VertexBuffer(GLenum type = GL_ARRAY_BUFFER);
	~VertexBuffer();

	void Bind();
	void Unbind();

	void Set(GLsizeiptr size, const GLvoid *data, GLenum usage = GL_STATIC_DRAW);
	
	template <class _type>
	void Set(const std::vector<_type> &data, size_t size = 1, GLenum usage = GL_STATIC_DRAW) {
		Set(data.size() * sizeof(_type) * size, &data[0], usage);
	}

	void EnableAttribute(GLuint index, GLint size, GLenum type = GL_FLOAT, GLboolean normalized = GL_FALSE, GLsizei stride = 0, const GLvoid *data = 0);
	void DisableAttribute(GLuint index);

protected:
	GLuint _id;
	GLenum _type;
};

} // namespace en61
