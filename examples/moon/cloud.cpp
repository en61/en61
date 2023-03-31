#include "cloud.h"

#include <glm/gtx/transform.hpp>
#include <memory>

Cloud::Cloud() {
	_mesh = std::make_shared<CloudMesh>();
	_shader = std::make_shared<Shader>();
	_texture = std::make_shared<Texture>();
	_position = glm::vec3(-0.3f, 1, -3.f);

	_texture->Load("../assets/blue_particle.png");
	_shader->Load("../assets/particle.vert", "../assets/particle.frag", "../assets/particle.geom");

	AddTexture(_texture);
	SetShader(_shader);
	SetMesh(_mesh);
}


void Cloud::Render(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &proj) {

	glDepthMask(false);

	auto translated_model = glm::translate(model, _position);
	Object::Render(translated_model, view, proj);

	glDepthMask(true);
}
