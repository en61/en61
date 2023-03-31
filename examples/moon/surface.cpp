#include "surface.h"

Surface::Surface() {
	_mesh = std::make_shared<Mesh>();
	_shader = std::make_shared<Shader>();
	_texture = std::make_shared<Texture>();

	_shader->Load("../assets/surface.vert", "../assets/surface.frag");
	_mesh->Load("../assets/surface.obj");
	_texture->Load("../assets/moon.png");

	SetMesh(_mesh);
	SetShader(_shader);
	AddTexture(_texture);
}
