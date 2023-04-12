#include "glm/ext/matrix_transform.hpp"
#include <core/scene/object.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace en61 {

void Object::Render(const glm::mat4 &view, const glm::mat4 &projection) {

	glm::mat4 model = glm::translate(glm::mat4(1.0f), _position);
	
	if (_shader) {
		_shader->Use();
		_shader->SetMatrix4("model", model);
		_shader->SetMatrix4("view", view);
		_shader->SetMatrix4("projection", projection);
		_shader->SetInteger("colorTexture", 0);
	}

	for (size_t i = 0; i < _textures.size(); i++) {
		_textures[i]->Bind(i);
	}

	if (_mesh)
		_mesh->Draw();
}

void Object::SetMesh(Ref<MeshInterface> mesh) {
	_mesh = mesh;
}

void Object::SetShader(Ref<Shader> shader) {
	_shader = shader;
}

void Object::AddTexture(Ref<Texture> texture) {
	if (_textures.size() > 30) {
		std::cerr << "Texture skipped: 30 textures limit reached!" << std::endl;
		return;
	}
	_textures.push_back(texture);
}

glm::vec3 Object::GetPosition() const {
	return _position;
}

void Object::SetPosition(const glm::vec3 &position) {
	_position = position;
}

} // namespace en61
