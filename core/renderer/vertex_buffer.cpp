#include <core/renderer/vertex_buffer.h>

namespace en61 {

VertexBuffer::VertexBuffer(GLenum type)
	: _type(type) {
	glGenBuffers(1, &_id);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &_id);
}

void VertexBuffer::bind() {
	glBindBuffer(_type, _id);
}

void VertexBuffer::unbind() {
	glBindBuffer(_type, 0);
}

void VertexBuffer::set(GLsizeiptr size, const GLvoid *data, GLenum usage) {
	this->bind();
	glBufferData(_type, size, data, usage);
}

void VertexBuffer::enable_attribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *data) {
	this->bind();
	glVertexAttribPointer(index, size, type, normalized, stride, data);
	glEnableVertexAttribArray(index);
}

void VertexBuffer::disable_attribute(GLuint index) {
	glDisableVertexAttribArray(index);
}

} // namespace en61
