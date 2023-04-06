#include "cube.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

Cube::Cube() {
	_mesh = std::make_shared<Mesh>();
	_shader = std::make_shared<Shader>();
	_texture = std::make_shared<Texture>();

	_mesh->Load("../assets/cube.obj");
	_shader->Load("../assets/cube.frag", "../assets/cube.vert");
	_texture->Load("../assets/redcube.png");

	SetMesh(_mesh);
	SetShader(_shader);
	AddTexture(_texture);
}
