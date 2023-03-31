#include <core/scene/object.h>

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace en61 {

void Object::Render(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection) {
	_shader->Use();
	_shader->SetMatrix4("model", model);
	_shader->SetMatrix4("view", view);
	_shader->SetMatrix4("projection", projection);
	_shader->SetInteger("colorTexture", 0);

	for (size_t i = 0; i < _textures.size(); i++) {
		_textures[i]->Bind(i);
	}

	if (_mesh)
	    _mesh->Draw();
}

void Object::SetMesh(std::shared_ptr<IMesh> mesh) {
	_mesh = mesh;
}

void Object::SetShader(std::shared_ptr<Shader> shader) {
	_shader = shader;
}

void Object::AddTexture(std::shared_ptr<Texture> texture) {
	if (_textures.size() > 30) {
		std::cerr << "Texture skipped: 30 textures limit reached!" << std::endl;
		return;
	}
	_textures.push_back(texture);
}

} // namespace en61
