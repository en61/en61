#include <core/renderer/shader.h>

#include <core/resource.h>

#include <fstream>
#include <sstream>
#include <iostream>

namespace en61 {

Shader::~Shader() {
	glDeleteProgram(_id);
}

std::optional<std::string> Shader::LoadShaderCode(const std::string &path) {
	
	std::ifstream stream(path, std::ios::in);
	if (!stream.is_open()) {
		std::cerr << "Error: cannot load shader file: " << path << std::endl;
		return std::nullopt;
	}
	std::stringstream sstr;
	sstr << stream.rdbuf();
	std::string code = sstr.str();
	return stream.close(), code;
}

void Shader::CreateShaders() {
	for (auto &shader: _shaders) {
		if (auto code = LoadShaderCode(shader.path)) {
			shader.code = code.value();
			std::cout << "Loaded shader file: " << shader.path << std::endl;
		}
	}
}

GLuint Shader::Id() const {
	return _id;
}

GLuint Shader::GetUniformLocation(const std::string &name) {
	return glGetUniformLocation(Id(), name.c_str());
}

GLuint Shader::GetAttribLocation(const std::string &name) {
	return glGetAttribLocation(Id(), name.c_str());
} 

void Shader::Use() {
	glUseProgram(Id());
}


void Shader::CheckShaderError(const GLuint shader_id) {
	GLint result;
	int log_length;

	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

	if (log_length > 0) {
		std::cerr << "shader compilation errors:" << std::endl;
		std::string message; 
		message.reserve(log_length + 1);
		glGetShaderInfoLog(shader_id, log_length, NULL, &message[0]);
		std::cerr << message << std::endl;
	}
}

void Shader::CheckProgramError() {
	GLint result;
	int log_length;

	glGetProgramiv(_id, GL_LINK_STATUS, &result);
	glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &log_length);

	if (log_length > 0) {
		std::cerr << "program compilation errors:" << std::endl;
		std::string message; 
		message.reserve(log_length + 1);
		glGetProgramInfoLog(_id, log_length, NULL, &message[0]);
		std::cerr << message << std::endl;
	}
}

GLuint Shader::CompileShader(const std::string &code, unsigned shader_type) {
	GLuint shader_id = glCreateShader(shader_type);
	const char *shader_src = code.c_str();

	glShaderSource(shader_id, 1, &shader_src, NULL);
	glCompileShader(shader_id);
	CheckShaderError(shader_id);

	return shader_id;
}


void Shader::CompileShaders() {

	std::list<GLuint> _shader_ids;
	for (auto shader: _shaders) {
		_shader_ids.push_back(CompileShader(shader.code, shader.type));
	}

	_id = glCreateProgram();
	
	for (auto shader_id: _shader_ids) {
		glAttachShader(_id, shader_id);
	}

	glLinkProgram(_id);
	CheckProgramError();

	for (auto shader_id: _shader_ids) {
		glDetachShader(_id, shader_id);
		glDeleteShader(shader_id);
	}
}


void Shader::Load(const std::string &vpath, const std::string &fpath) {
	_shaders.emplace_back(vpath, GL_VERTEX_SHADER);
	_shaders.emplace_back(fpath, GL_FRAGMENT_SHADER);

	CreateShaders(); 
	CompileShaders();	
}

void Shader::Load(const std::string &vpath, const std::string &fpath, const std::string &gpath) {
	_shaders.emplace_back(vpath, GL_VERTEX_SHADER);
	_shaders.emplace_back(gpath, GL_GEOMETRY_SHADER);
	_shaders.emplace_back(fpath, GL_FRAGMENT_SHADER);

	CreateShaders(); 
	CompileShaders();	
}

template <typename _Type>
void Shader::Set(const std::string &name, const _Type &type) {
	std::cerr << "No uniform setter for " << typeid(_Type).name() << " type found!" << std::endl;
}

template <>
void Shader::Set(const std::string &name, const glm::vec4 &vec) {
	Use();
	glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(vec));
}

template <>
void Shader::Set(const std::string &name, const glm::vec3 &vec) {
	Use();
	glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(vec));
}

template <>
void Shader::Set(const std::string &name, const glm::mat4 &matrix) {
	Use();
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

template <>
void Shader::Set(const std::string &name, const GLfloat &value) {
	Use();
	glUniform1f(GetUniformLocation(name), value);
}

template <>
void Shader::Set(const std::string &name, const GLint &value) {
	Use();
	glUniform1i(GetUniformLocation(name), value);
}

} // namespace en61
