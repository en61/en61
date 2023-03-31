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
	
	GLuint Id() const;
	GLuint GetUniformLocation(const std::string &name);
	GLuint GetAttribLocation(const std::string &name);

	void Use();
	void Load(const std::string &vpath, const std::string &fpath);
	void Load(const std::string &vpath, const std::string &fpath, const std::string &gpath);

	void SetMatrix4(const std::string &name, const glm::mat4 &matrix);
	void SetVec4(const std::string &name, const glm::vec4 &vec);
	void SetInteger(const std::string &name, GLint value);

protected:
	void CreateShaders();
	void CompileShaders();

	void CheckShaderError(const GLuint id);
	void CheckProgramError();

	GLuint CompileShader(const std::string &code, unsigned shader_type);
	std::string LoadShaderCode(const std::string &path);

protected:
	GLuint _id;
	std::list<ShaderFile> _shaders;
};

} // namespace en61
