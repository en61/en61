#pragma once

#include <core/opengl.h>

#include <string>

namespace en61 {

class Texture {
public:
	Texture(size_t type = GL_TEXTURE_2D) : _type(type) {}

	void Load(const std::string &path, size_t slot = 0);
	void Bind(size_t slot = 0);

protected:
	GLuint _id;
	size_t _type;
};

} // namespace en61
