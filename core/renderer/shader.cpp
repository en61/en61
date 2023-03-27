#include <core/renderer/shader.h>

#include <core/resource.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <list>

#include <glm/gtc/type_ptr.hpp>

namespace en61 {

Shader::~Shader() {
	glDeleteProgram(_id);
}

std::string Shader::load_shader_code(const std::string &path) {
	
	std::ifstream stream(path, std::ios::in);
	if (!stream.is_open()) {
	    std::cerr << "cannot load shader file: " << path << std::endl;
	    return "";
	}
	std::stringstream sstr;
	sstr << stream.rdbuf();
	std::string code = sstr.str();
	return stream.close(), code;
}

void Shader::create_shaders() {
	for (auto &shader: _shaders) {
		shader.code = load_shader_code(shader.path);
		std::cout << "Loaded shader file: " << shader.path << std::endl;
	}
}

GLuint Shader::id() const {
	return _id;
}

GLuint Shader::get_uniform_location(const std::string &name) {
	return glGetUniformLocation(id(), name.c_str());
}

GLuint Shader::get_attrib_location(const std::string &name) {
	return glGetAttribLocation(id(), name.c_str());
} 

void Shader::use() {
	glUseProgram(id());
}


void Shader::check_shader_error(const GLuint shader_id) {
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

void Shader::check_program_error() {
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

GLuint Shader::compile_shader(const std::string &code, unsigned shader_type) {
	GLuint shader_id = glCreateShader(shader_type);
	const char *shader_src = code.c_str();

	glShaderSource(shader_id, 1, &shader_src, NULL);
	glCompileShader(shader_id);
	check_shader_error(shader_id);

	return shader_id;
}


void Shader::compile_shaders() {

	std::list<GLuint> _shader_ids;
	for (auto shader: _shaders) {
		_shader_ids.push_back(compile_shader(shader.code, shader.type));
	}

	_id = glCreateProgram();
	
	for (auto shader_id: _shader_ids) {
	    glAttachShader(_id, shader_id);
	}

	glLinkProgram(_id);
	check_program_error();

	for (auto shader_id: _shader_ids) {
		glDetachShader(_id, shader_id);
		glDeleteShader(shader_id);
	}
}


void Shader::load(const std::string &vpath, const std::string &fpath) {
	_shaders.emplace_back(vpath, GL_VERTEX_SHADER);
	_shaders.emplace_back(fpath, GL_FRAGMENT_SHADER);

	create_shaders(); 
	compile_shaders();	
}
void Shader::load(const std::string &vpath, const std::string &fpath, const std::string &gpath) {
	_shaders.emplace_back(vpath, GL_VERTEX_SHADER);
	_shaders.emplace_back(gpath, GL_GEOMETRY_SHADER);
	_shaders.emplace_back(fpath, GL_FRAGMENT_SHADER);

	create_shaders(); 
	compile_shaders();	
}

void Shader::set_vec4(const std::string &name, const glm::vec4 &vec) {
	use();
	glUniform4fv(get_uniform_location(name), 1, glm::value_ptr(vec));
}

void Shader::set_matrix4(const std::string &name, const glm::mat4 &matrix) {
	use();
	glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::set_integer(const std::string &name, GLint value) {
	use();
	glUniform1i(get_uniform_location(name), value);
}

} // namespace en61
