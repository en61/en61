#include "surface.h"

Surface::Surface() {
	_mesh = std::make_shared<Mesh>();
	_shader = std::make_shared<Shader>();
	_texture = std::make_shared<Texture>();

	_shader->load("../assets/surface.vert", "../assets/surface.frag");
	_mesh->load("../assets/surface.obj");
	_texture->load("../assets/moon.png");

	set_mesh(_mesh);
	set_shader(_shader);
	add_texture(_texture);
}
