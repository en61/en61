#pragma once

#include <core/opengl.h>

#include <list>
#include <string>
#include <optional>

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
	
	GLuint Id() const;
	GLuint GetUniformLocation(const std::string &name);
	GLuint GetAttribLocation(const std::string &name);

	void Use();
	void Load(const std::string &vpath, const std::string &fpath);
	void Load(const std::string &vpath, const std::string &fpath, const std::string &gpath);

	template <typename _Type>
	void SetUniform(const std::string &name, const _Type &type) {
		WrongTypeUniform(typeid(_Type));
	}

protected:
	void CreateShaders();
	void CompileShaders();

	void CheckShaderError(const GLuint id);
	void CheckProgramError();

	void WrongTypeUniform(const std::type_info &info);

	GLuint CompileShader(const std::string &code, unsigned shader_type);
	std::optional<std::string> LoadShaderCode(const std::string &path);

protected:
	GLuint _id;
	std::list<ShaderFile> _shaders;
};


} // namespace en61
