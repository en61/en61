#include <core/renderer/vertex_buffer.h>

namespace en61 {

VertexBuffer::VertexBuffer(GLenum type)
	: _type(type) {
	glGenBuffers(1, &_id);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &_id);
}

void VertexBuffer::Bind() {
	glBindBuffer(_type, _id);
}

void VertexBuffer::Unbind() {
	glBindBuffer(_type, 0);
}

void VertexBuffer::Set(GLsizeiptr size, const GLvoid *data, GLenum usage) {
	this->Bind();
	glBufferData(_type, size, data, usage);
}

void VertexBuffer::EnableAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *data) {
	this->Bind();
	glVertexAttribPointer(index, size, type, normalized, stride, data);
	glEnableVertexAttribArray(index);
}

void VertexBuffer::DisableAttribute(GLuint index) {
	glDisableVertexAttribArray(index);
}

} // namespace en61
