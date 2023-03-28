#include "cloud.h"

#include <glm/gtx/transform.hpp>
#include <memory>

Cloud::Cloud() {
	_mesh = std::make_shared<CloudMesh>();
	_shader = std::make_shared<Shader>();
	_texture = std::make_shared<Texture>();
	_position = glm::vec3(-0.3f, 1, -3.f);

	_texture->load("../assets/blue_particle.png");
	_shader->load("../assets/particle.vert", "../assets/particle.frag", "../assets/particle.geom");

	add_texture(_texture);
	set_shader(_shader);
	set_mesh(_mesh);
}


void Cloud::render(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &proj) {

	glDepthMask(false);

	auto translated_model = glm::translate(model, _position);
	Object::render(translated_model, view, proj);

	glDepthMask(true);
}
