#pragma once

#include <core/scene/object.h>
#include <core/renderer/texture.h>
#include <core/renderer/shader.h>
#include <memory>

#include "cloud_mesh.h"

class Cloud: public Object {
public:
	Cloud();

	void Render(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &proj) override;

protected:
	std::shared_ptr<CloudMesh> _mesh;
	std::shared_ptr<Shader> _shader;
	std::shared_ptr<Texture> _texture;

	glm::vec3 _position;
};
