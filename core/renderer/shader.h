#pragma once

#include <core/opengl.h>
#include <core/renderer/shader.h>

#include <list>
#include <string>

namespace en61 {

struct ShaderFile {
	std::string path;
	std::string code;
	GLuint type;

	ShaderFile() = default;
	ShaderFile(const std::string &p, GLuint t)
		: path(p), type(t) {}
};

class Shader {
public:

	Shader() = default;
	~Shader();
	
	GLuint id() const;
	GLuint get_uniform_location(const std::string &name);
	GLuint get_attrib_location(const std::string &name);

	void use();
	void load(const std::string &vpath, const std::string &fpath);
	void load(const std::string &vpath, const std::string &fpath, const std::string &gpath);

	void set_matrix4(const std::string &name, const glm::mat4 &matrix);
	void set_vec4(const std::string &name, const glm::vec4 &vec);
	void set_integer(const std::string &name, GLint value);

protected:
	void create_shaders();
	void compile_shaders();

	void check_shader_error(const GLuint id);
	void check_program_error();

	GLuint compile_shader(const std::string &code, unsigned shader_type);
	std::string load_shader_code(const std::string &path);

protected:
	GLuint _id;
	std::list<ShaderFile> _shaders;
};

} // namespace en61
