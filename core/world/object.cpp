#include <core/world/object.h>

#include <iostream>

namespace en61 {

void Object::Render(const glm::mat4 &view, const glm::mat4 &projection) {

	SetUniform("model", GetModelMatrix());
	SetUniform("view", view);
	SetUniform("projection", projection);
	SetUniform("colorTexture", 0);

	DrawTextures();
	DrawModel();
}

void Object::RenderOutline(const glm::mat4 &view, const glm::mat4 &projection) {
	glLineWidth(7);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	Object::Render(view, projection);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Object::DrawTextures() {
	for (size_t i = 0; i < _textures.size(); i++) {
		_textures[i]->Bind(i);
	}
}

bool Object::HasShader() const {
	return static_cast<bool>(_shader);
}

bool Object::HasModel() const {
	return static_cast<bool>(_model);
}

Ref<Shader> Object::GetShader() const {
	assert(HasShader() && "shader=null");
	return _shader;
}

Ref<ModelBase> Object::GetModel() const {
	assert(HasModel() && "model=null");
	return _model;
}

void Object::DrawModel() {
	GetModel()->Draw();
}

void Object::SetModel(Ref<ModelBase> model) {
	_model = model;
}

void Object::SetModel(Ref<Model> model) {
	_model = model;
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

glm::mat4 Object::GetModelMatrix() const {
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
