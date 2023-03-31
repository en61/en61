#include <core/renderer/texture.h>
#include <core/resource.h>

#include <iostream>
#include <cstring>

#include <stb/stb_image.h>

namespace en61 {

void Texture::Load(const std::string &path, size_t slot) {
	int width, height, channels;
	stbi_uc *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	if (!data) {
		std::cerr << "could not load texture: " << path << std::endl;
		return;
	}
	
	std::cout << "Texture successfully loaded: " << path << std::endl;

	int format = channels == 4 ? GL_RGBA : GL_RGB;

	glActiveTexture(GL_TEXTURE0 + slot);
	glGenTextures(1, &_id);
	glBindTexture(_type, _id);
	
	glTexImage2D(_type, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(_type);
	glTexParameteri(_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(_type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	stbi_image_free(data);
}

void Texture::Bind(size_t slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(_type, _id);
}

} // namespace en61
