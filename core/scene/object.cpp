#include <core/scene/object.h>

#include <iostream>

namespace en61 {

void Object::Render(const glm::mat4 &view, const glm::mat4 &projection) {

	SetUniform("model", GetModel());
	SetUniform("view", view);
	SetUniform("projection", projection);
	SetUniform("colorTexture", 0);

	DrawTextures();
	DrawMesh();
}

void Object::DrawTextures() {
	for (size_t i = 0; i < _textures.size(); i++) {
		_textures[i]->Bind(i);
	}
}

void Object::DrawMesh() {
	assert(_mesh && "mesh=null");
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

glm::mat4 Object::GetModel() const {
	auto model = glm::mat4(1.0f);
	model = glm::translate(model, _position);
	model = glm::scale(model, _scale);
	return model;
}

glm::vec3 Object::GetPosition() const {
	return _position;
}

void Object::SetPosition(const glm::vec3 &position) {
	_position = position;
}

void Object::SetScale(const glm::vec3 &scale) {
	_scale = scale;
}

} // namespace en61
