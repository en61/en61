#pragma once

#include <core/renderer/vertex_array.h>
#include <core/renderer/vertex_buffer.h>
#include <core/renderer/texture.h>
#include <core/common.h>

namespace en61 {

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

class Mesh {
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<Texture> textures);
	void Draw();

protected:
	Ref<VertexArray> _array;
	Ref<VertexBuffer> _vertexBuffer, _indexBuffer;

	std::vector<Vertex> _vertices;
	std::vector<unsigned> _indices;
	std::vector<Texture> _textures;

};

} // namespace en61
