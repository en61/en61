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

	virtual void render(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection);

	void add_texture(std::shared_ptr<Texture> texture);
	void set_mesh(std::shared_ptr<Mesh> mesh);
	void set_shader(std::shared_ptr<Shader> shader);

protected:
	std::vector<std::shared_ptr<Texture>> _textures;
	std::shared_ptr<Shader> _shader;
	std::shared_ptr<Mesh> _mesh;
};

} // namespace en61
