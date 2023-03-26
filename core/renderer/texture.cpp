#include <core/renderer/texture.h>
#include <core/resource.h>

#include <iostream>
#include <cstring>

#include <stb/stb_image.h>

namespace en61 {

void Texture::load_dds(const std::string &path, size_t slot) {

	std::string full_path = locate_file(path);

	static constexpr auto FOURCC_DXT1 = 0x31545844; // Equivalent to "DXT1" in ASCII
	static constexpr auto FOURCC_DXT3 = 0x33545844; // Equivalent to "DXT3" in ASCII
	static constexpr auto FOURCC_DXT5 = 0x35545844; // Equivalent to "DXT5" in ASCII

#ifndef GL_EXT_texture_compression_s3tc
#define GL_EXT_texture_compression_s3tc 1
	
	constexpr auto GL_COMPRESSED_RGB_S3TC_DXT1_EXT  = 0x83F0;
	constexpr auto GL_COMPRESSED_RGBA_S3TC_DXT1_EXT = 0x83F1;
	constexpr auto GL_COMPRESSED_RGBA_S3TC_DXT3_EXT = 0x83F2;
	constexpr auto GL_COMPRESSED_RGBA_S3TC_DXT5_EXT = 0x83F3;
	
#endif

	unsigned char header[124];

	FILE *fp; 
 
	/* try to open the file */ 
	fp = fopen(full_path.c_str(), "rb"); 
	if (fp == NULL) {
		std::cout << full_path << " could not be opened" << std::endl;
		return;
	}
   
	char filecode[4]; 
	fread(filecode, 1, 4, fp); 
	if (strncmp(filecode, "DDS ", 4) != 0) { 
		fclose(fp); 
		return; 
	}
	
	fread(&header, 124, 1, fp); 

	unsigned int height      = *(unsigned int*)&(header[8 ]);
	unsigned int width	     = *(unsigned int*)&(header[12]);
	unsigned int linearSize	 = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC      = *(unsigned int*)&(header[80]);

 
	unsigned char * buffer;
	unsigned int bufsize;
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize; 
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char)); 
	fread(buffer, 1, bufsize, fp); 
	fclose(fp);

	unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4; 
	unsigned int format;
	switch(fourCC) 
	{ 
	case FOURCC_DXT1: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; 
		break; 
	case FOURCC_DXT3: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; 
		break; 
	case FOURCC_DXT5: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; 
		break; 
	default: 
		free(buffer); 
		return; 
	}

	// Create one OpenGL texture
	//GLuint textureID;
	glActiveTexture(GL_TEXTURE0 + slot);
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);	
	
	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16; 
	unsigned int offset = 0;

	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) 
	{ 
		unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize; 
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset); 
	 
		offset += size; 
		width  /= 2; 
		height /= 2; 

		if(width < 1) width = 1;
		if(height < 1) height = 1;

	} 

	free(buffer); 

	return;
}

void Texture::load(const std::string &path, size_t slot) {
	std::string full_path = locate_file(path);

	int width, height, channels;
	stbi_uc *data = stbi_load(full_path.c_str(), &width, &height, &channels, 0);
	if (!data) {
		std::cerr << "could not load texture: " << full_path << std::endl;
		return;
	}
	
	std::cout << "Texture successfully loaded: " << full_path << std::endl;

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

void Texture::bind(size_t slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(_type, _id);
}

} // namespace en61
