#pragma once

#include <core/scene/object.h>
#include <core/renderer/shader.h>
#include <core/renderer/mesh.h>
#include <core/renderer/texture.h>

#include <memory>

using namespace en61;

class Surface: public Object { 
public:
	Surface();

protected:
	std::shared_ptr<Mesh> _mesh;
	std::shared_ptr<Shader> _shader;
	std::shared_ptr<Texture> _texture;
};
