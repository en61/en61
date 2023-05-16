#include <core/renderer/vertex_array.h>

namespace en61 {

VertexArray::VertexArray()
	: _id(0) {
	glGenVertexArrays(1, &_id);
	Bind();
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &_id);
}

void VertexArray::Bind() {
	glBindVertexArray(_id);
}

void VertexArray::Unbind() {
	glBindVertexArray(0);
}

void VertexArray::DrawTriangles(size_t count) {
	this->Bind();
	glDrawArrays(GL_TRIANGLES, 0, count);
}

void VertexArray::DrawPoints(size_t count) {
	this->Bind();
	glDrawArrays(GL_POINTS, 0, count);
}

void VertexArray::DrawLines(size_t count) {
	this->Bind();
	glDrawArrays(GL_LINES, 0, count);
}

} // namespace en61
