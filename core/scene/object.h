#pragma once

#include <core/renderer/shader.h>
#include <core/renderer/texture.h>
#include <core/renderer/model.h>
#include <core/common.h>

#include <vector>

namespace en61 {

class Object {
public:
	Object() = default;

	virtual void Render(const glm::mat4 &view, const glm::mat4 &projection);

	void AddTexture(Ref<Texture> texture);
	void SetModel(Ref<ModelInterface> model);
	void SetShader(Ref<Shader> shader);

	void SetPosition(const glm::vec3 &position);
	void SetScale(const glm::vec3 &scale);

	void DrawModel();
	void DrawTextures();

	glm::mat4 GetModelMatrix() const;
	glm::vec3 GetPosition() const;

	bool HasShader() const;
	bool HasModel() const;

	Ref<Shader> GetShader() const;
	Ref<ModelInterface> GetModel() const;

	template <class _Type>
	void SetUniform(const std::string &name, _Type value) {
		GetShader()->SetUniform<_Type>(name, value);
	}

protected:
	std::vector<Ref<Texture>> _textures;
	Ref<Shader> _shader;
	Ref<ModelInterface> _model;
	glm::vec3 _position = { 0, 0, 0 };
	glm::vec3 _scale = { 1, 1, 1 };
};

} // namespace en61
