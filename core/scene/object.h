#pragma once

#include <core/renderer/shader.h>
#include <core/renderer/texture.h>
#include <core/renderer/mesh.h>

#include <memory>
#include <vector>

namespace en61 {

class Object {
public:
	Object() = default;

	virtual void Render(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection);

	void AddTexture(std::shared_ptr<Texture> texture);
	void SetMesh(std::shared_ptr<IMesh> mesh);
	void SetShader(std::shared_ptr<Shader> shader);

	virtual glm::mat4 GetModel();

protected:
	std::vector<std::shared_ptr<Texture>> _textures;
	std::shared_ptr<Shader> _shader;
	std::shared_ptr<IMesh> _mesh;
};

} // namespace en61
