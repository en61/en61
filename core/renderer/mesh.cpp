#include <core/renderer/mesh.h>

namespace en61 {


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<Texture> textures)
	: _vertices(vertices), _indices(indices), _textures(textures) {

	_array = MakeRef<VertexArray>();
	_vertexBuffer = MakeRef<VertexBuffer>(GL_ARRAY_BUFFER);
	_indexBuffer = MakeRef<VertexBuffer>(GL_ELEMENT_ARRAY_BUFFER);

	_array->Bind();

	_vertexBuffer->Set(_vertices);
	_indexBuffer->Set(_indices);

	_vertexBuffer->EnableAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	_vertexBuffer->EnableAttribute(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	_vertexBuffer->EnableAttribute(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	_array->Unbind();
}

void Mesh::Draw() {
	size_t diffuseNr = 1;
	size_t specularNr = 1;

	for(size_t i = 0; i < _textures.size(); i++) {
		// todo: Use Texture
	}

	_array->Bind();
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);

	_array->Unbind();

	glActiveTexture(GL_TEXTURE0);
}

} // namespace en61
