#pragma once

#include <core/renderer/shader.h>
#include <core/renderer/texture.h>
#include <core/renderer/mesh.h>
#include <core/common.h>
#include <vector>

namespace en61 {

class Object {
public:
	Object() = default;

	virtual void Render(const glm::mat4 &view, const glm::mat4 &projection);

	void AddTexture(Ref<Texture> texture);
	void SetMesh(Ref<MeshInterface> mesh);
	void SetShader(Ref<Shader> shader);
	
	glm::vec3 GetPosition() const;
	void SetPosition(const glm::vec3 &position);

protected:
	std::vector<Ref<Texture>> _textures;
	Ref<Shader> _shader;
	Ref<MeshInterface> _mesh;
	glm::vec3 _position = { 0.f, 0.f, 0.f };
};

} // namespace en61
