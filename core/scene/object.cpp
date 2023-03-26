#include <core/scene/object.h>

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace en61 {

void Object::render(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection) {
	_shader->use();
	_shader->set_matrix4("model", model);
	_shader->set_matrix4("view", view);
	_shader->set_matrix4("projection", projection);
	_shader->set_integer("colorTexture", 0);

	for (size_t i = 0; i < _textures.size(); i++) {
		_textures[i]->bind(i);
	}

	if (_mesh)
	    _mesh->draw();
}

void Object::set_mesh(std::shared_ptr<Mesh> mesh) {
	_mesh = mesh;
}

void Object::set_shader(std::shared_ptr<Shader> shader) {
	_shader = shader;
}

void Object::add_texture(std::shared_ptr<Texture> texture) {
	if (_textures.size() > 30) {
		std::cerr << "Texture skipped: 30 textures limit reached!" << std::endl;
		return;
	}
	_textures.push_back(texture);
}

} // namespace en61
