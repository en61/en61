#include <core/renderer/vertex_array.h>

namespace en61 {

VertexArray::VertexArray()
	: _id(0) {
	glGenVertexArrays(1, &_id);
	bind();
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &_id);
}

void VertexArray::bind() {
	glBindVertexArray(_id);
}

void VertexArray::unbind() {
	glBindVertexArray(0);
}

void VertexArray::draw_triangles(size_t count) {
	this->bind();
	glDrawArrays(GL_TRIANGLES, 0, count);
}

void VertexArray::draw_points(size_t count) {
	this->bind();
	glDrawArrays(GL_POINTS, 0, count);
}

} // namespace en61
